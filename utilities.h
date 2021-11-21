#ifndef UTILITIES_H
#define UTILITIES_H

void quicksort_only_indices(int *a, int low, int high);
int partition_only_indices(int *a, int low, int high);
void quicksort_indices_and_values(int *a, int *b, int low, int high);
void swap(int* a, int* b);
int partition_indices_and_values(int *a, int *b, int low, int high);
int row_col_dot_product(int *a, int start1, int end1, int start2, int end2);

#endif