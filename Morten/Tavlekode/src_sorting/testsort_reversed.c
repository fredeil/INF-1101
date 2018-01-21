/* Author: Aage Kvalnes <aage@cs.uit.no> */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "sort.h"
#include "time.h"

#define MAXNUM_DATA     (1024*32)

typedef struct data data_t;
struct data {
    int key;
};


void dump_data(data_t *d, int left, int right)
{
    int i;

    for (i = left; i < right; i++) {
        printf("%d: %d\n", i, d[i].key);
    }
}

int mycmpfunc(data_t *d, int a, int b)
{
    if (d[a].key < d[b].key) {
        return -1;
    } else if (d[a].key > d[b].key) {
        return 1;
    } else {
        return 0;
    }
}


int mycmpfunc2(data_t *d, int a, int b)
{
    if (d[a].key > d[b].key) {
        return -1;
    } else if (d[a].key < d[b].key) {
        return 1;
    } else {
        return 0;
    }
}


int myexchfunc(data_t *d, int a, int b)
{
    data_t tmp;

    memcpy(&tmp, d + a, sizeof(data_t));
    memcpy(d + a, d + b, sizeof(data_t));
    memcpy(d + b, &tmp, sizeof(data_t));
    return 0;
}


int main(int argc, char **argv)
{
    int i, j;
    FILE *f;
    unsigned long long t1, t2;
    data_t *data;

    data = (data_t*) malloc(sizeof(data_t)*MAXNUM_DATA);
    if (data == NULL) {
        printf("Unable to allocate memory\n");
        exit(1);
    }
    
    if (argc <= 1) {
        printf("Usage: %s <output file>\n",
               argv[0]);
        exit(1);
    }


    f = fopen(argv[1], "w");
    if (f == NULL) {
        printf("Unable to open output file\n");
        exit(1);
    }

    srand(121212);
    //for (i = 8; i < MAXNUM_DATA; i *= 2) {
    for (i = 2048; i < MAXNUM_DATA; i += 2048) {
        for (j = 0; j < i; j++) {
            data[j].key = rand();
        }
        
        /* Sort from high to low (cmpfunc2) */
        sort(data, 0, i-1, (cmpfunc_t)mycmpfunc2, (exchfunc_t)myexchfunc);

        /* and sort again from low to high */
        t1 = gettime();
        sort(data, 0, i-1, (cmpfunc_t)mycmpfunc, (exchfunc_t)myexchfunc);
        t2 = gettime();
        fprintf(f, "%d %d\n", i, (int)(t2-t1));
    }
    fclose(f);

    return 0;

}
