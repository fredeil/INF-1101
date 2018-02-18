#include "set.h"

struct set
{
    void* hey;
};

set_t *set_create(cmpfunc_t cmpfunc);
void set_destroy(set_t *set);
int set_size(set_t *set);
void set_add(set_t *set, void *elem);
int set_contains(set_t *set, void *elem);
set_t *set_union(set_t *a, set_t *b);
set_t *set_intersection(set_t *a, set_t *b);
set_t *set_difference(set_t *a, set_t *b);
set_t *set_copy(set_t *set);

struct set_iter
{
    void* hey;
};

set_iter_t *set_createiter(set_t *set);
void set_destroyiter(set_iter_t *iter);
int set_hasnext(set_iter_t *iter);
void *set_next(set_iter_t *iter);
