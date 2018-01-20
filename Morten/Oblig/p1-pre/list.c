#include "list.h"
#include "common.h"
#include <assert.h>

typedef struct node node_t;
struct node
{
    void *elem;
    node_t *next;
};

struct list
{
    node_t *head;
    cmpfunc_t cmpfunc;
    int length;
};


list_t *list_create(cmpfunc_t cmpfunc)
{
    list_t *list = malloc(sizeof(list_t));
    if(list == NULL)
    {
        fatal_error("out of memory");
    } 

    list->head = NULL; 
    int length = 0;

    return list;
}

void list_destroy(list_t *list)
{
    node_t *node, *tmp;

    node = list->head;

    while(node != NULL)
    {
        tmp = node->next;
        free(node);
        node = tmp;
    }

    free(list);
}


int list_size(list_t *list)
{
    return list->length;
}

void list_addfirst(list_t *list, void *elem)
{
    node_t *node = malloc(sizeof(node_t));
    if(node == NULL)
    {
        fatal_error("out of memory");
    }

    node->elem = elem;
    node->next = list->head;
    list->head = node;
    list->length++;
}

void list_addlast(list_t *list, void *elem)
{
    node_t *node = malloc(sizeof(node_t));
    if(node == NULL)
    {
        fatal_error("out of memory");
    }

    node_t *tmp;
    tmp = list->head;
    
    while(tmp->next != NULL)
    {
        tmp = tmp->next;
    }

    node->elem = elem;
    node->next = NULL;
    tmp->next = node;
    list->length++;
}

void *list_popfirst(list_t *list)
{
    if(list->head == NULL)
    {
        return NULL;
    }

    void *retval;
    node_t *free_node;

    retval = list->head->elem;
    free_node = list->head;
    list->head = list->head->next;
    list->length--;
    free(free_node);

    return retval;
}

void *list_poplast(list_t *list)
{
    if(list->head == NULL)
    {
        return NULL;
    }
    
    void *retval;
    node_t *free_node = list->head;
    node_t *prev_node;

    while(free_node->next != NULL)
    {
        prev_node = free_node;
        free_node = free_node->next;
    }

    retval = free_node->elem;
    prev_node->next = NULL;
    list->length--;
    free(free_node);

    return retval;
}

int list_contains(list_t *list, void *elem)
{
    if(list->head == NULL)
    {
        return 0;
    }

    node_t *node = list->head;

    while(node->next != NULL)
    {
        if(list->cmpfunc(node, elem) == 0)
        {
            return 1;
        }
        node = node->next;
    } 

    return 0;
}


void list_sort(list_t *list);

struct list_iter
{
    node_t *node;
};

list_iter_t *list_createiter(list_t *list)
{
    list_iter_t *iter = malloc(sizeof(list_iter_t));

    if(iter == NULL)
    {
        fatal_error("out of memory");
    }

    iter->node = list->head;

    return iter;
}

void list_destroyiter(list_iter_t *iter)
{
    free(iter);
}

int list_hasnext(list_iter_t *iter)
{
    if(iter->node->next == NULL)
    {
        return 0;
    }
    
    return 1;
}

void *list_next(list_iter_t *iter)
{
    void *retval = iter->node->elem;
    iter->node = iter->node->next;

    return retval;
}
