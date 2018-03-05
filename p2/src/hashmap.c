#include "map.h"
#include "list.h"
#include "common.h"

struct map
{

};

map_t *map_create(cmpfunc_t cmpfunc, hashfunc_t hashfunc)
{
    if(cmpfunc == NULL)
    {
        fatal_error("cmpfunc null");
    }

    if(hashfunc == NULL)
    {
        fatal_error("hashfunc null");
    }

    return NULL;
}

void map_destroy(map_t *map)
{

}

void map_put(map_t *map, void *key, void *value)
{
    if(map == NULL)
    {
        fatal_error("map null");
    }

    if(key == NULL || value == NULL)
    {
        fatal_error("key/value pair null");
    }

}

int map_haskey(map_t *map, void *key)
{
    if(map == NULL)
    {
        fatal_error("map null");
    }

    if(key == NULL)
    {
        fatal_error("key null");
    }
}

void *map_get(map_t *map, void *key)
{
    if(map == NULL)
    {
        fatal_error("map null");
    }

    if(key == NULL)
    {
        fatal_error("key null");
    }
}