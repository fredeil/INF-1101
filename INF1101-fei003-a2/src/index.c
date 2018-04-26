#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

#include "set.h"
#include "map.h"
#include "index.h"
#include "list.h"
#include "common.h"

struct index
{
    map_t *hashmap;
    double num_docs;
    char *current_word;
    list_iter_t *iterator;
};

typedef struct data
{
    char *path;
    double term_in_document;
    double terms_in_document;
    double tf;
    double idf;
} data_t;

data_t *data_create()
{
    data_t *d = calloc(1, sizeof(data_t));
    if (d == NULL)
    {
        fatal_error("Out of memory");
    }

    return d;
}

void data_destroy(data_t *d)
{
    if (NULL != d)
    {
        if (NULL != d->path)
        {
            free(d->path);
        }
        free(d);
    }
}

index_t *index_create()
{
    index_t *index = calloc(1, sizeof(index_t));
    if (index == NULL)
    {
        fatal_error("Out of memory");
    }

    index->num_docs = 0;
    index->iterator = NULL;
    index->current_word = NULL;
    index->hashmap = map_create(compare_strings, hash_string);

    return index;
}

void index_destroy(index_t *index)
{
    map_destroy(index->hashmap, free, free);
    if (index->iterator != NULL)
    {
        list_destroyiter(index->iterator);
    }

    free(index);
}

int compare_data(void *a, void *b)
{
    return compare_strings(((data_t *)a)->path, ((data_t *)b)->path);
}

/*
 * Adds the given path to the given index, and index the given
 * list of words under that path.
 * NOTE: It is the responsibility of index_addpath() to deallocate (free)
 *       'path' and the contents of the 'words' list.
 */
void index_addpath(index_t *index, char *path, list_t *words)
{
    list_iter_t *iter = list_createiter(words);
    while (list_hasnext(iter))
    {
        char *current_word = list_next(iter);

        // Word was already inserted to the hashmap
        if (map_haskey(index->hashmap, current_word) == 1)
        {
            set_t *set = map_get(index->hashmap, current_word);

            // Check if the set contains our path
            if (set_contains(set, &(data_t){.path = path}) == 1)
            {
                set_iter_t *iter = set_createiter(set);
                while (set_hasnext(iter))
                {
                    data_t *data = set_next(iter);
                    if (compare_strings(data->path, path) == 0)
                    {
                        data->term_in_document++;
                        break;
                    }
                }

                set_destroyiter(iter);
            }
            else
            {
                // Set didn't contain the data, so we create it
                data_t *data = data_create();
                data->path = path;
                data->term_in_document = 1;
                data->terms_in_document = list_size(words);
                set_add(set, data);
            }
        }
        else
        {
            // Insert new word into hashmap
            data_t *data = data_create();
            set_t *set = set_create(compare_data);

            data->path = path;
            data->term_in_document = 1;
            data->terms_in_document = list_size(words);

            set_add(set, data);
            map_put(index->hashmap, current_word, set);
        }
    }

    list_destroyiter(iter);
    index->num_docs++;
}

int compare_query(void *a, void *b)
{
    double aa = ((query_result_t *)a)->score;
    double bb = ((query_result_t *)b)->score;

    return aa > bb ? -1 : aa < bb ? 1 : 0;
}

list_t *index_query(index_t *index, list_t *query, char **errmsg)
{
    index->iterator = list_createiter(query);
    if (list_hasnext(index->iterator))
    {
        index->current_word = list_next(index->iterator);
    }

    list_t *list = NULL;
    set_t *set = parse_query(index, errmsg);

    if (set != NULL)
    {
        set_iter_t *iter = set_createiter(set);
        list = list_create(compare_query);

        while (set_hasnext(iter))
        {
            query_result_t *query_result = malloc(sizeof(query_result_t));
            data_t *data = set_next(iter);
            data->tf = data->term_in_document / data->terms_in_document;
            data->idf = log(index->num_docs / ((double)set_size(set)));

            query_result->path = data->path;
            query_result->score = data->tf * data->idf;
            list_addfirst(list, query_result);
        }

        set_destroyiter(iter);
    }

    list_destroyiter(index->iterator);
    list_sort(list);

    return list;
}

// something
set_t *parse_query(index_t *index, char **errmsg)
{
    set_t *terms = parse_andterm(index, errmsg);
    if (compare_strings(index->current_word, "ANDNOT") == 0)
    {
        if (list_hasnext(index->iterator))
        {
            index->current_word = list_next(index->iterator);
            return set_difference(terms, parse_query(index, errmsg));
        }
    }

    return terms;
}

// something
set_t *parse_andterm(index_t *index, char **errmsg)
{
    set_t *terms = parse_orterm(index, errmsg);

    if (compare_strings(index->current_word, "AND") == 0)
    {
        if (list_hasnext(index->iterator))
        {
            index->current_word = list_next(index->iterator);
            return set_intersection(terms, parse_andterm(index, errmsg));
        }
    }

    return terms;
}

// Something
set_t *parse_orterm(index_t *index, char **errmsg)
{
    set_t *terms = parse_term(index, errmsg);
    if (compare_strings(index->current_word, "OR") == 0)
    {
        if (list_hasnext(index->iterator))
        {
            index->current_word = list_next(index->iterator);
            return set_union(terms, parse_orterm(index, errmsg));
        }
    }

    return terms;
}

set_t *parse_term(index_t *index, char **errmsg)
{
    set_t *set = NULL;

    // // If the query starts with an opening ()
    // if (compare_strings(index->current_word, "(") == 0)
    // {
    // //     if (list_hasnext(index->iterator))
    // //     {
    // //         index->current_word = list_next(index->iterator);
    // //     }

    //     set = parse_query(index, errmsg);

    //     // if (list_hasnext(index->iterator))
    //     // {
    //     //     index->current_word = list_next(index->iterator);
    //     // }

    //     // if (compare_strings(index->current_word, ")") != 0)
    //     // {
    //     //     *errmsg = "Something went wrong..";
    //     // }
    //     // else if (list_hasnext(index->iterator))
    //     // {
    //     //     index->current_word = list_next(index->iterator);
    //     // }
    // }
    // if (map_haskey(index->hashmap, index->current_word) == 1)
    // {
    //     // This happens if the query has no parenthesis

    //     set = map_get(index->hashmap, index->current_word);

    //     if (list_hasnext(index->iterator))
    //     {
    //         index->current_word = list_next(index->iterator);
    //     }
    // }

    return set;
}