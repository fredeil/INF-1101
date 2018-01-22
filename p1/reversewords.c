#include "list.h"
#include "common.h"

int string_compare(void *p1, void *p2)
{
   return strcasecmp((char*)p1, (char*)p2);
}

void list_print(list_t *list)
{
    puts("\n");
    
    list_iter_t *iter = list_createiter(list);
    while (list_hasnext(iter))
    {
        printf("%s \n", (char*)list_next(iter));
    }

    list_destroyiter(iter);
}

void list_reverse(list_t *list)
{
    list_iter_t *iter = list_createiter(list);
   
    while(list_hasnext(iter))
    {
        list_addfirst(list, list_poplast(list));
    }

    list_destroyiter(iter);
}

int main(int argc, char *argv[])
{
    list_t *list = list_create(string_compare);

    tokenize_file(fopen(argv[1], "r"), list);

    list_print(list);
    list_reverse(list);
    list_print(list);

    return 0;
}