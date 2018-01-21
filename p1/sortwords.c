#include "list.h"
#include "common.h"

int string_compare(void *p1, void *p2)
{
   return strcmp((char*)p1, (char*)p2);
}

void print_list(list_t *list)
{
    puts("\n");
    
    list_iter_t *iter = list_createiter(list);
    while (list_hasnext(iter))
    {
        printf("%s \n", list_next(iter));
    }

    list_destroyiter(iter);
}

int main(int argc, char **argv)
{
    list_t *list = list_create(string_compare);

    list_addfirst(list, "a");
    list_addfirst(list, "b");
    list_addfirst(list, "c");

    print_list(list);

    list_sort(list);

    print_list(list);
    
    list_destroy(list);

    return 0;
}
