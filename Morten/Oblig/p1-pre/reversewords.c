#include "list.h"
#include "common.h"
#include <string.h>
#include <stdio.h>


int stringComparer(void *str1, void *str2)
{
	return strcmp((char*)str1, (char*)str2);
}

int main(int argc, char **argv)
{
    list_t *list = list_create(stringComparer);

    void *ptr1 = "Morten";
    void *ptr2 = "Morten";

    printf("Lenght: %d\n", list_size(list));
    list_addfirst(list, ptr1);
    list_addfirst(list, ptr2);
    printf("Lenght: %d\n", list_size(list));



    printf("%d\n", list_contains(list,"Morten"));

    return 0;
}

