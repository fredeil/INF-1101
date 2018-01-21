#include "common.h"
#include "list.h"

int string_compare(void *p1, void *p2)
{
   return strcmp((char*)p1, (char*)p2);
}

int main(int argc, char **argv)
{
    list_t *list = list_create(string_compare);

    list_addfirst(list, "hei");
    printf("hei %s \n", list_popfirst(list));

    return 0;
}
