#ifndef SORT_H
#define SORT_H

#define SWAP(x, y) \
    int t;         \
    t = x;         \
    x = y;         \
    y = t;

typedef void (*sortfunc_t)(int *, int);
void bubblesort(int *data, int size);
void insertion_sort(int *data, int size);
void selection_sort(int *data, int size);
void merge_sort(int *data, int size);
void heap_sort(int *data, int size);
void quicksort(int *data, int size);

#endif
