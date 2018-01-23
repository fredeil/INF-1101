#include "list.h"
#include "common.h"

int string_compare(void *p1, void *p2)
{
   return strcasecmp((char*)p1, (char*)p2);
}

void print_list(list_t *list)
{
    list_iter_t *iter = list_createiter(list);
    while (list_hasnext(iter))
    {
        printf("%s ", (char*)list_next(iter));
    }

    list_destroyiter(iter);
}

void reverse_list(list_t **list)
{
    list_t *newlist = list_create(string_compare);
    list_iter_t *iter = list_createiter(*list);
   
    while(list_hasnext(iter)) 
    {
        list_addfirst(newlist, list_next(iter));
    }

    *list = newlist;

    list_destroyiter(iter);
}

int main(int argc, char *argv[])
{
    list_t *list = list_create(string_compare);

    tokenize_file(fopen(argv[1], "r"), list);

    print_list(list);
    puts("\n");    
    reverse_list(&list);
    print_list(list);
    puts("\n");    

    return 0;
}