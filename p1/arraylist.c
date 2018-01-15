#include "list.h"
#include "common.h"


struct list;
typedef struct list list_t;

void list_destroy(list_t *list)
{

}

int list_size(list_t *list)
{
    return 0;
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

struct list_iter;

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