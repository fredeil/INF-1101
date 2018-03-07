#include "map.h"

#define THRESHOLD 10

typedef struct map_item map_item_t;
struct map_item
{
    void *key;
    void *value;
    size_t hash_value;
};

struct map
{
    size_t max_elements;
    size_t num_elements;
    list_t **table;
    cmpfunc_t cmpfunc;
    hashfunc_t hashfunc;
};

map_t *map_create(cmpfunc_t cmpfunc, hashfunc_t hashfunc)
{
    if(cmpfunc == NULL)
    {
        fatal_error("map_create: cmpfunc null");
    }

    if(hashfunc == NULL)
    {
        fatal_error("map_create: hashfunc null");
    }

    map_t *map = malloc(sizeof(map_t));

    if(map == NULL)
    { 
        fatal_error("map_create: map null");
    }

    list_t **list = (list_t**)calloc(THRESHOLD, sizeof(list_t*));

    if(list == NULL)
    {
        free(map);
        fatal_error("map_create: list null");
    }
    
    map->table = list;
    map->num_elements = 0;
    map->cmpfunc = cmpfunc;
    map->hashfunc = hashfunc;
    map->max_elements = THRESHOLD;

    return map;
}

static void map_resize(map_t *map)
{
    if(map == NULL)
    {
        fatal_error("map_resize: map null");
    }
}

void map_destroy(map_t *map)
{
    if(map == NULL)
    {
        fatal_error("map_destroy: map null");
    }

}

void map_put(map_t *map, void *key, void *value)
{
    if(map == NULL)
    {
        fatal_error("map_put: map null");
    }

    if(key == NULL || value == NULL)
    {
        fatal_error("mapt_put: key/value pair null");
    }

}

int map_haskey(map_t *map, void *key)
{
    if(map == NULL)
    {
        fatal_error("map_haskey: map null");
    }

    if(key == NULL)
    {
        fatal_error("map_haskey: key null");
    }
}

void *map_get(map_t *map, void *key)
{
    if(map == NULL)
    {
        fatal_error("map_get: map null");
    }

    if(key == NULL)
    {
        fatal_error("map_get: key null");
    }
}