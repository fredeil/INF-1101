#include "list.h"
#include "common.h"
#include <assert.h>

struct list 
{
    int size;
    void *data;
    cmpfunc_t comparer;
};

list_t *list_create(cmpfunc_t cmpfunc)
{
    list_t *list = malloc(sizeof(list_t));

    assert(list != NULL);

    list->size = 0;
    list->comparer = cmpfunc;

    return list;
}

void list_destroy(list_t *list)
{

}

int list_size(list_t *list)
{
    assert(list != NULL);
    return list->size;
}

void list_addfirst(list_t *list, void *elem)
{

}

void list_addlast(list_t *list, void *elem)
{

}

void *list_popfirst(list_t *list)
{

}

void *list_poplast(list_t *list)
{
    
}

int list_contains(list_t *list, void *elem)
{
    return 0;
}

void list_sort(list_t *list)
{

}

struct list_iter 
{
 
};

list_iter_t *list_createiter(list_t *list)
{

}

void list_destroyiter(list_iter_t *iter)
{

}

int list_hasnext(list_iter_t *iter)
{

}

void *list_next(list_iter_t *iter)
{

}

int main(void) 
{
    list_t *list = list_create(NULL);
    puts("mordi");
    printf("Size: %d\n", list_size(list));
}