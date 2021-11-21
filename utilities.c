#include "utilities.h"

void quicksort_only_indices(int *a, int low, int high) {
    if (low < high) {
        int pi = partition_only_indices(a, low, high);
        quicksort_only_indices(a, low, pi - 1);  // Before pi
        quicksort_only_indices(a, pi + 1, high); // After pi
    }
}


int partition_only_indices(int *a, int low, int high) {
    int pivot = a[high];  
    int  i = (low - 1);
    for(int j = low; j <= high- 1; j++) {
        // If current element is smaller than the pivot
        if (a[j] < pivot) {
            i++;    // increment index of smaller element
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i + 1], &a[high]);
    return (i + 1);
}

void quicksort_indices_and_values(int *a, int *b, int low, int high) {
    if (low < high) {
        int pi = partition_indices_and_values(a, b, low, high);
        quicksort_indices_and_values(a, b, low, pi - 1);  // Before pi
        quicksort_indices_and_values(a, b, pi + 1, high); // After pi
    }
}

int partition_indices_and_values(int *a, int *b, int low, int high) {
    int pivot = a[high];  
    int  i = (low - 1);
    for(int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        if (a[j] < pivot) {
            i++;    // increment index of smaller element
            swap(&a[i], &a[j]);
            swap(&b[i], &b[j]);
        }
    }
    swap(&a[i + 1], &a[high]);
    swap(&b[i + 1], &b[high]);
    return (i + 1);
}

void swap(int* a, int* b) {
    int t = *a; 
    *a = *b; 
    *b = t; 
}

int row_col_dot_product(int *a, int start1, int end1,
                           int start2, int end2) {
  int i = start1;
  int j = start2;
  int count = 0;

  while (i < end1 && j < end2) {
    if (a[i] < a[j])
      i++;
    else if (a[j] < a[i])
      j++;
    else {
      count++;
      i++;
      j++;
    }
  }

  return count;
}