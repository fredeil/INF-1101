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

int main(int argc, char *argv[])
{
    list_t *list = list_create(string_compare);

    FILE *fp = fopen(argv[1], "r");
    
    tokenize_file(fp, list);

    print_list(list);
    puts("\n");
    list_sort(list);
    print_list(list);
    puts("\n");

    return 0;
}
