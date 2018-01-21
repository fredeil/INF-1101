#include <stdio.h>
#include <stdbool.h>
#include "common.h"
#include "list.h"

typedef struct node node_t;
struct node 
{
    void *elem;
    node_t *next;
};

struct list 
{
    int lenght;
    node_t *head;
    cmpfunc_t cmpfunc;
};

list_t *list_create(cmpfunc_t cmpfunc)
{
    list_t *list = malloc(sizeof(list_t));
    if(list == NULL) 
    {
        fatal_error("Out of memory.");
    }

    list->lenght = 0;
    list->head = NULL;

    return list;
}

void list_destroy(list_t *list)
{
    node_t *node;
    node_t *temp;

    node = list->head;
    while(node != NULL)
    {
         temp = node;
         node = node->next;
         free(temp);    
    }

    free(list);
}

int list_size(list_t *list)
{
    return list->lenght;
}

void list_addfirst(list_t *list, void *elem)
{
    node_t *node = malloc(sizeof(node_t));
    if(node == NULL)
    {
        fatal_error("Out of memory.");
    }

    node->elem = elem;
    node->next = list->head;
    list->head = node;
    list->lenght++;
}

void list_addlast(list_t *list, void *elem)
{
    node_t *node = malloc(sizeof(node_t));
    if(node == NULL)
    {
        fatal_error("Out of memory.");    
    }

    node->elem = elem;
    node->next = NULL;

    node_t *current = list->head;
    while(current->next != NULL) 
    {
        current = current->next;
    }

    current->next = node;
    list->lenght++;
}

void *list_popfirst(list_t *list)
{
    if(list->head == NULL)
    {
        return NULL;
    }
    
    node_t *node = list->head;
    void *retval = node->elem;
    list->head = node->next;
    list->lenght--;
    free(node);

    return retval;
}

void *list_poplast(list_t *list)
{
    if(list->head == NULL)
    {
        return NULL;
    }
    
    void *retval;
    node_t *prev;

    node_t *node = list->head;
    while(node->next != NULL)
    {
        prev = node;
        node = node->next;
    }

    retval = node->elem;
    prev->next = NULL;
    list->lenght--;
    free(node);

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
        if(list->cmpfunc(node->elem, elem) == 0)
        {
            return 1;
        }

        node = node->next;
    }

    return 0;
}

void list_sort(list_t *list)
{

}

/**** Iterator *****/
 
struct list_iter
{
    node_t *node;
};

list_iter_t *list_createiter(list_t *list)
{
    list_iter_t *iter = malloc(sizeof(list_iter_t));
    if(iter == NULL)
    {
        fatal_error("Out of memory");
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
  return NULL;
}
