#include "set.h"
#include "list.h"
#include "common.h"
#include <stdlib.h>

struct set
{
    list_t *list;
    cmpfunc_t cmpfunc;
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
    set->cmpfunc = cmpfunc;

    return set;
}

void set_destroy(set_t *set)
{
    if(set == NULL) 
    {
        return;
    }

   list_destroy(set->list);
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

    // Element already in set
    if(list_contains(set->list, elem))
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
        fatal_error("Set is null: set_contains");
    }

    return list_contains(set->list, elem);
}

set_t *set_union(set_t *a, set_t *b)
{
    if(a == NULL || b == NULL)
    {
        fatal_error("Set a or b is null");
    }

    set_t *set = set_create(a->cmpfunc);
    set_iter_t *itera = set_createiter(a);
    set_iter_t *iterb = set_createiter(b);

    while(set_hasnext(itera))
    {
        set_add(set, set_next(itera));
    }
    set_destroyiter(itera);

    while(set_hasnext(iterb))
    {
        set_add(set, set_next(iterb));
    }
    set_destroyiter(iterb);

   return set;
}

set_t *set_intersection(set_t *a, set_t *b)
{
    if(a == NULL || b == NULL)
    {
        fatal_error("Set a or b is null");
    }

    set_t *set = set_create(a->cmpfunc);
    set_iter_t *iter = set_createiter(a);
    void *tmp;

    while(set_hasnext(iter)) 
    {
        tmp = set_next(iter);
        if(set_contains(b, tmp))
        {
            set_add(set, tmp);
        }
    }
    
    set_destroyiter(iter);
    return set;
}

set_t *set_difference(set_t *a, set_t *b)
{
    if(a == NULL || b == NULL)
    {
        fatal_error("Set a or b is null");
    }

    set_t *set = set_create(a->cmpfunc);
    set_iter_t *iter = set_createiter(a);
    void *tmp;

    while(set_hasnext(iter)) 
    {
        tmp = set_next(iter);
        if(!set_contains(b, tmp))
        {
            set_add(set, tmp);
        }
    }
    
    set_destroyiter(iter);
    return set;
}

set_t *set_copy(set_t *set)
{
    if(set == NULL)
    {
        fatal_error("Set is null: set_copy");
    }

    set_t *cpy = set_create(set->cmpfunc);
    list_t *list = list_create(set->cmpfunc);
    list_iter_t *iter = list_createiter(set->list);

    while(list_hasnext(iter))
    {
        list_addlast(list, list_next(iter));
    }

    list_destroyiter(iter);

    cpy->list = list;
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
        fatal_error("Set is null: set_createiter");
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
    return list_next(iter->iter);
}
