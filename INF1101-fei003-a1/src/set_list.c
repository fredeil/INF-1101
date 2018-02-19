#include "set.h"
#include "list.h"
#include "common.h"
#include <stdlib.h>

#define DEBUG 0

struct set
{
    list_t *list;
};

set_t *set_create(cmpfunc_t cmpfunc)
{
    list_t *list = list_create(cmpfunc);
    set_t *set = malloc(sizeof(set_t));

    if(set == NULL || list == NULL)
    {
        fatal_error("Out of memory");
    }

    set->list = list;
    return set;
}

void set_destroy(set_t *set)
{
    if(set == NULL) 
    {
        return;
    }

   list_destroy((list_t*)set->list);
   free(set);
}

int set_size(set_t *set)
{
    if(set == NULL)
    {
        return 0;
    }
    
    return list_size(set->list);
}

void set_add(set_t *set, void *elem)
{
    if(set == NULL)
    {
        return;
    }

    list_addfirst(set->list, elem);
    list_sort(set->list);
}

int set_contains(set_t *set, void *elem)
{
    if(set == NULL)
    {
        fatal_error("Set is NULL");
    }

    return list_contains(set->list, elem);
}

set_t *set_union(set_t *a, set_t *b)
{
   return set_create(NULL);
}

set_t *set_intersection(set_t *a, set_t *b)
{
    return set_create(NULL);
}

set_t *set_difference(set_t *a, set_t *b)
{
    return set_create(NULL);
}

set_t *set_copy(set_t *set)
{
    set_t *cpy = malloc(sizeof(set_t));
    memcpy(cpy, set, sizeof(set_t));

    return cpy;
}

struct set_iter
{
    list_iter_t *iter;
};

set_iter_t *set_createiter(set_t *set)
{
    if(set == NULL)
    {
        fatal_error("Set is null");
    }

    set_iter_t *iter = malloc(sizeof(set_iter_t));
    iter->iter = list_createiter(set->list);

    return iter;
}

void set_destroyiter(set_iter_t *iter)
{
    list_destroyiter(iter->iter);
    free(iter);
}

int set_hasnext(set_iter_t *iter)
{
    return list_hasnext(iter->iter);
}

void *set_next(set_iter_t *iter)
{
    list_next(iter->iter);
}
