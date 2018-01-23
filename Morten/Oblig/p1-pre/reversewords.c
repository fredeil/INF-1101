#include "list.h"
#include "common.h"
#include <string.h>
#include <stdio.h>

void bubbleSort(list_t *list)
{
    list_iter_t *left = list_createiter(list);
    list_iter_t *right = list_createiter(list);
    list_next(right);
}

void printList(list_t *list)
{
    list_iter_t *iter = list_createiter(list);

    while(list_hasnext(iter) == 1)
    {
        printf("%s\n", list_next(iter));
    }
} 

int stringComparer(void *str1, void *str2)
{
	return strcmp((char*)str1, (char*)str2);
}

int main(int argc, char **argv)
{
    list_t *list = list_create(stringComparer);

    void *ptr1 = "Morten";
    void *ptr2 = "Morten";

    list_addfirst(list, "Morten");
    list_addfirst(list, "fredrik");
    list_addfirst(list, "Kenneth");
    list_addfirst(list, "Alexander");



    printList(list);

    return 0;
}

