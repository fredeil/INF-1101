#ifndef SORT_H
#define SORT_H

// Macros:
#define SWAP(x,y) int t;t=x;x=y;y=t;

typedef void (*sortfunc_t)(int*, int);

// Functions that implement the sorting algorithms
void bubblesort(int *data, int size);

void insertion_sort(int *data, int size);

void selection_sort(int *data, int size);

void merge_sprt(int *data, int size);

void heap_sort(int *data, int size);

void quicksort(int *data, int size);

#endif
