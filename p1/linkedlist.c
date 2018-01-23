#include "list.h"
#include <stdio.h>
#include <string.h>

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
    list->cmpfunc = cmpfunc;

    return list;
}

void list_destroy(list_t *list)
{
    node_t *temp = NULL;
    node_t *node = list->head;

    while(node != NULL)
    {
         temp = node;
         node = node->next;
         free(temp);
         temp = NULL;  
    }

    free(list);
    list = NULL;
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

    if(list->head == NULL)
    {
        list_addfirst(list, elem);
        return;
    }

    node_t *current = list->head;
    while(current->next != NULL) 
    {
        current = current->next;
    }

    node->elem = elem;
    node->next = NULL;

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
    node = NULL;

    return retval;
}

void *list_poplast(list_t *list)
{
    if(list->head == NULL)
    {
        return NULL;
    }
    
    void *retval = NULL;
    node_t *prev = NULL;

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
    node = NULL;

    return retval;
}

int list_contains(list_t *list, void *elem)
{
    if(list->head == NULL)
    {
        return 0;
    }

    node_t *node = list->head;
    while(node != NULL)
    {
        if(list->cmpfunc(node->elem, elem) == 0)
        {
            return 1;
        }

        node = node->next;
    }

    return 0;
}

// Naive but easy to only swap the data
void swap_elem(node_t *left, node_t *right)
{
   if(left == NULL || right == NULL)
   {
       return;
   }

   void *tmp = left->elem;
   left->elem = right->elem;
   right->elem = tmp;
}

void list_sort(list_t *list)
{
    // Nothing to sort
    if(list->head == NULL)
    {
        fatal_error("list_sort: param null");
    }

    node_t *current = NULL;
    cmpfunc_t compare = list->cmpfunc;

    // Bubble Sort inspo: https://en.wikipedia.org/wiki/Bubble_sort#Pseudocode_implementation
    for(int i = 0; i < list_size(list); i++)
    {
        current = list->head;
        while (current->next != NULL)
        {
            if (compare(current->elem, current->next->elem) > 0)
            { 
                swap_elem(current, current->next);
            }

            current = current->next;
        }
    }
}

/**** Iterator *****/
struct list_iter
{
    node_t *node;
    list_t *list;
};

list_iter_t *list_createiter(list_t *list)
{
    if(list == NULL) 
    {
        return NULL;
    }

    list_iter_t *iter = malloc(sizeof(list_iter_t));
    if(iter == NULL)
    {
        fatal_error("Out of memory.");
    }


    iter->list = list;
    iter->node = list->head;

    return iter;
}

void list_destroyiter(list_iter_t *iter)
{
    free(iter);
    iter = NULL;
}

int list_hasnext(list_iter_t *iter)
{
    if(iter->node == NULL)
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
