#include "list.h"
#include "common.h"

int string_compare(void *p1, void *p2)
{
   return strcasecmp((char*)p2, (char*)p1);
}

void print_list(list_t *list)
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
    list_t *newlist = list_create(string_compare);

    list_iter_t *iter = list_createiter(list);
   
    for(int i = 0; i < list_size(list); i++) 
    {
        list_addfirst(newlist, list_popfirst(list));
    }

    memcpy(list, newlist, sizeof(int));

    list_destroy(newlist);
    list_destroyiter(iter);
}

int main(int argc, char *argv[])
{
    list_t *list = list_create(string_compare);

    FILE *fp = fopen(argv[1], "r");
    
    tokenize_file(fp, list);

    print_list(list);
    list_reverse(list);
    print_list(list);

    return 0;
}