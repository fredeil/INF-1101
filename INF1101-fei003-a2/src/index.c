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

#define DEBUG 1

struct index
{
    map_t *hashmap;
    double num_docs;
    char *current_word;
    list_iter_t *iterator;
};

typedef struct doc
{
    char *path;
    double termt;
    double nterms;
} doc_t;

// Compares the paths inside two given docs
int compare_docs(void *a, void *b)
{
    return compare_strings(((doc_t *)a)->path, ((doc_t *)b)->path);
}

// Creates a new, empty index
index_t *index_create()
{
    index_t *index = calloc(1, sizeof(index_t));
    if (index == NULL)
        fatal_error("Out of memory");

    index->hashmap = map_create(compare_strings, hash_string);

    return index;
}


// Destroys the given index
void index_destroy(index_t *index)
{
    map_destroy(index->hashmap, free, (void*)set_destroy);
    list_destroyiter(index->iterator);

    free(index);
}

// Adds the given path to the given index, and index the given list of words under that path
void index_addpath(index_t *index, char *path, list_t *words)
{
    index->num_docs++;
    list_iter_t *iter = list_createiter(words);

    while (list_hasnext(iter))
    {
        char *current_word = list_next(iter);

        // Word was already inserted to the hashmap
        if (map_haskey(index->hashmap, current_word) == 1)
        {
            set_t *set = map_get(index->hashmap, current_word);

            // Check if the set contains our path
            doc_t *doc = calloc(1, sizeof(doc_t));
            if(doc == NULL)
                fatal_error("Out of memory.");
            
            doc->path = strdup(path);

            if (set_contains(set, doc) == 1)
            {
                set_iter_t *iter = set_createiter(set);
                while (set_hasnext(iter))
                {
                    doc_t *doc = set_next(iter);
                    if (compare_strings(doc->path, path) == 0)
                    {
                        doc->termt++;
                        break;
                    }
                }

                free(doc->path);
                free(doc);
                set_destroyiter(iter);
            }
            else
            {
                // Set didn't contain the data, so we create it
                doc_t *doc = calloc(1, sizeof(doc_t));
                if (doc == NULL)
                    fatal_error("Out of memory");

                doc->termt = 1;
                doc->path = strdup(path);
                doc->nterms = list_size(words);

                set_add(set, doc);
            }
        }
        else
        {
            // Insert new word into hashmap
            doc_t *doc = calloc(1, sizeof(doc_t));
            if (doc == NULL)
                fatal_error("Out of memory");

            set_t *set = set_create(compare_docs);

            doc->path = path;
            doc->termt = 1;
            doc->nterms = list_size(words);

            set_add(set, doc);
            map_put(index->hashmap, current_word, set);
        }
    }

    list_destroyiter(iter);
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
        index->current_word = list_next(index->iterator);

    list_t *list = NULL;
    set_t *set = parse_query(index, errmsg);

    if (set != NULL)
    {
        set_iter_t *iter = set_createiter(set);
        list = list_create(compare_query);

        while (set_hasnext(iter))
        {

            query_result_t *query_result = malloc(sizeof(query_result_t));
            if (query_result == NULL)
                fatal_error("Out of memory");

            doc_t *doc = set_next(iter);
            query_result->path = doc->path;
            query_result->score = (doc->termt / doc->nterms) * log(index->num_docs / (double)set_size(set));
            list_addfirst(list, query_result);
        }

        set_destroyiter(iter);
        list_sort(list);
    }

#if DEBUG
    if (set == NULL)
        puts("Set null");
#endif

    list_destroyiter(index->iterator);

    return list;
}

// query ::= andterm | andterm "ANDNOT" query
set_t *parse_query(index_t *index, char **errmsg)
{
    // andterm
    set_t *term = parse_andterm(index, errmsg);

    // andterm "ANDNOT" query
    if (compare_strings(index->current_word, "ANDNOT") == 0)
    {
        if (list_hasnext(index->iterator))
        {
            index->current_word = list_next(index->iterator);
            return set_difference(term, parse_query(index, errmsg));
        }
    }

    return term;
}

// andterm ::= orterm | orterm "AND" andterm
set_t *parse_andterm(index_t *index, char **errmsg)
{
    // orterm
    set_t *term = parse_orterm(index, errmsg);

    // orterm "AND" andterm
    if (compare_strings(index->current_word, "AND") == 0)
    {
        if (list_hasnext(index->iterator))
        {
            index->current_word = list_next(index->iterator);
            return set_intersection(term, parse_andterm(index, errmsg));
        }
    }

    return term;
}

// orterm ::= term | term "OR" orterm
set_t *parse_orterm(index_t *index, char **errmsg)
{
    // term
    set_t *term = parse_term(index, errmsg);

    // term "OR" orterm
    if (compare_strings(index->current_word, "OR") == 0)
    {
        if (list_hasnext(index->iterator))
        {
            index->current_word = list_next(index->iterator);
            #if DEBUG
                printf("ORTERM: %s\n", index->current_word);
            #endif
            return set_union(term, parse_orterm(index, errmsg));
        }
    }

    return term;
}

// term ::= "(" query ")" | <word>
set_t *parse_term(index_t *index, char **errmsg)
{
    set_t *set = NULL;

    // "(" query ")"
    if (compare_strings(index->current_word, "(") == 0)
    {
        if (list_hasnext(index->iterator))
            index->current_word = list_next(index->iterator);

        set = parse_query(index, errmsg);

        if (list_hasnext(index->iterator))
            index->current_word = list_next(index->iterator);

        if (compare_strings(index->current_word, ")") != 0)
        {
            *errmsg = "Missing \")\"";
            return NULL;
        }

        if (list_hasnext(index->iterator))
            index->current_word = list_next(index->iterator);
    }

    // <word>
    if (map_haskey(index->hashmap, index->current_word) == 1)
    {
        set = map_get(index->hashmap, index->current_word);
        
        if (list_hasnext(index->iterator))
            index->current_word = list_next(index->iterator);

#if DEBUG
        printf("PARSE_TERM: %s\n", index->current_word);
#endif
    }

    return set;
}