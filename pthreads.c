#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <pthread.h>

#include "mmio.h"
#include "utilities.h"
#include "coo2csc.h"
#include <time.h>

// Number of triangles for each graph
// belgium_osm: 2.420
// com-Youtube: 3.056.386
// mycielskian13 : 0
// dblp-2010 : 1.676.652

int N;

int lower_A_nzs, *lower_A_rows, *lower_A_cols, *lower_A_values;

int *full_A_rows, *full_A_cols, *full_A_values_coo;

int *full_A_indices, *full_A_pointers, *full_A_values_csc;

int *lower_C_rows, *lower_C_cols, *lower_C_values;

int *full_C_rows, *full_C_cols, *full_C_values_coo;

int *full_C_indices, *full_C_pointers, *full_C_values_csc;

int res_nz = 0;

typedef struct {
    int worker_id;
    int starting_nonzero;
    int number_of_nonzeros;
} WorkerArgs;

WorkerArgs args[20];

pthread_mutex_t mutex;

void *calculate_sub_hadamard(void *arg) {
    WorkerArgs *dt = (WorkerArgs *)arg;
    int result;

    for (int i = dt->starting_nonzero; i < dt->starting_nonzero + dt->number_of_nonzeros; i++) {
        result = row_col_dot_product(full_A_indices,
                                    full_A_pointers[lower_A_rows[i]], full_A_pointers[lower_A_rows[i] + 1],
                                    full_A_pointers[lower_A_cols[i]], full_A_pointers[lower_A_cols[i] + 1]);
        
        if (result != 0) {
            pthread_mutex_lock(&mutex);

            lower_C_rows[res_nz] = lower_A_rows[i];
            lower_C_cols[res_nz] = lower_A_cols[i];
            lower_C_values[res_nz] = result;
            res_nz++;

            pthread_mutex_unlock(&mutex);
        }
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    clock_t begin = clock();
    char cwd[PATH_MAX];
    MM_typecode *matcode;

    if (argc < 2) {
        fprintf(stderr, "[!] You didn't enter the matrix path to calculate [!]\n");
        exit(1);
    }

    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        printf("[!] getcwd() encountered an error [!]\n");
        exit(1);
    }

    char *path_without_dot = argv[1] + 1;
    int return_code = mm_read_mtx_crd(strcat(cwd, path_without_dot), &N, &N, &lower_A_nzs, &lower_A_rows,&lower_A_cols, &lower_A_values, &matcode);

    if (return_code) {
        fprintf(stderr, "[!] Error while reading the file [!]");
    }

    for (int i = 0; i < lower_A_nzs; i++) {
        lower_A_rows[i]--;
        lower_A_cols[i]--;
    }

    full_A_rows = (int *)malloc(2 * lower_A_nzs * sizeof(int));
    full_A_cols = (int *)malloc(2 * lower_A_nzs * sizeof(int));
    full_A_values_coo = (int *)malloc(2 * lower_A_nzs * sizeof(int));

    for (int i = 0; i < lower_A_nzs; i++) {
    full_A_rows[i] = lower_A_rows[i];
    full_A_rows[lower_A_nzs + i] = lower_A_cols[i];
    full_A_cols[i] = lower_A_cols[i];
    full_A_cols[lower_A_nzs + i] = lower_A_rows[i];
    }

    full_A_indices = (int *)malloc(2 * lower_A_nzs * sizeof(int));
    full_A_pointers = (int *)malloc((N + 1) * sizeof(int));
    full_A_values_csc = (int *)malloc(2 * lower_A_nzs * sizeof(int));

    coo2csc(full_A_indices, full_A_pointers, full_A_values_csc, full_A_rows, full_A_cols, full_A_values_coo, 2 * lower_A_nzs, N, 0, 1);

    for (int i = 0; i < N; i++)
        quicksort_only_indices(full_A_indices, full_A_pointers[i], full_A_pointers[i + 1] - 1);

    lower_C_cols = (int *)malloc(2 * lower_A_nzs * sizeof(int));
    lower_C_rows = (int *)malloc(2 * lower_A_nzs * sizeof(int));
    lower_C_values = (int *)malloc(2 * lower_A_nzs * sizeof(int));

    int num_of_workers = atoi(argv[2]);

    pthread_t *workers = (pthread_t *)malloc(num_of_workers * sizeof(pthread_t));
    WorkerArgs *args = (WorkerArgs *)malloc(num_of_workers * sizeof(WorkerArgs));

    int nonzeros_per_worker = lower_A_nzs / num_of_workers;
    int remaining_nonzeros = lower_A_nzs % num_of_workers;
    int rc;

    pthread_mutex_init(&mutex, NULL);
    
    for (long i = 0; i < num_of_workers; i++) {
        args[i].worker_id = (int) i;
        args[i].number_of_nonzeros = nonzeros_per_worker;
        args[i].starting_nonzero = i * args[i].number_of_nonzeros;
        if (i == num_of_workers - 1)
            args[i].number_of_nonzeros += remaining_nonzeros;
        rc = pthread_create(&workers[i], NULL, calculate_sub_hadamard, (void *)&args[i]);
                            
    }
    
    for (long t = 0; t < num_of_workers; t++) {
        rc = pthread_join(workers[t], NULL);
        if (rc) {
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
    }
    
    pthread_mutex_destroy(&mutex);

    lower_C_cols = (int *)realloc(lower_C_cols, res_nz * sizeof(int));
    lower_C_rows = (int *)realloc(lower_C_rows, res_nz * sizeof(int));
    lower_C_values = (int *)realloc(lower_C_values, res_nz * sizeof(int));

    full_C_cols = (int *)malloc(2 * res_nz * sizeof(int));
    full_C_rows = (int *)malloc(2 * res_nz * sizeof(int));
    full_C_values_coo = (int *)malloc(2 * res_nz * sizeof(int));

    for (int i = 0; i < res_nz; i++) {
        full_C_rows[i] = lower_C_rows[i];
        full_C_rows[res_nz + i] = lower_C_cols[i];
        full_C_cols[i] = lower_C_cols[i];
        full_C_cols[res_nz + i] = lower_C_rows[i];
        full_C_values_coo[i] = lower_C_values[i];
        full_C_values_coo[res_nz + i] = lower_C_values[i];
    }

    full_C_pointers = (int *)malloc((N + 1) * sizeof(int));
    full_C_indices = (int *)malloc(2 * res_nz * sizeof(int));
    full_C_values_csc = (int *)malloc(2 * res_nz * sizeof(int));

    coo2csc(full_C_indices, full_C_pointers, full_C_values_csc, full_C_rows, full_C_cols, full_C_values_coo, 2 * res_nz, N, 0, 0);

    for (int i = 0; i < N; i++)
        quicksort_indices_and_values(full_C_indices, full_C_values_csc, full_C_pointers[i], full_C_pointers[i + 1] - 1);
    
    int *triangles_per_node = (int *)calloc(N, sizeof(int));

    for (int i = 0; i < N; i++) {
        for (int j = full_C_pointers[i]; j < full_C_pointers[i + 1]; j++)
            triangles_per_node[i] += full_C_values_csc[j];

        triangles_per_node[i] /= 2;
    }

    int sum = 0;
    for (int i = 0; i < N; i++)
        sum += triangles_per_node[i];
    
    clock_t end = clock();

    printf("Triangle count : %d\n", sum / 3);
    printf("Everything took %lf seconds\n", (double)(end-begin) / CLOCKS_PER_SEC);

    return 0;
}