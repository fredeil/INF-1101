/* Author: Aage Kvalnes <aage@cs.uit.no> */
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define STACK_MAXNUM_ITEMS   16

struct stack
{
    int maxitems;
    int numitems;
    void **items;
};

stack_t *stack_create(void)
{
    stack_t *s;

    s = calloc(1, sizeof(stack_t));
    if (s == NULL)
        goto error;
    s->items = malloc(sizeof(void*)*STACK_MAXNUM_ITEMS);
    if (s->items == NULL)
        goto error;
    s->numitems = 0;
    s->maxitems = STACK_MAXNUM_ITEMS;

    return s;
 error:
    if (s != NULL)
        free(s);
    return NULL;
}

void stack_destroy(stack_t *s)
{
    free(s->items);
    free(s);
}

int stack_push(stack_t *s, void *i)
{
    int  newmaxitems;
    void *newitems;

    // Resisze if needed
    if (s->numitems >= s->maxitems) {
        newmaxitems = s->maxitems*2;
        newitems = realloc(s->items, sizeof(void*)*newmaxitems);
        if (newitems == NULL)
            goto error;
        s->maxitems = newmaxitems;
        s->items = newitems;
    }

    // Push
    s->items[s->numitems] = i;
    s->numitems++;
    return 0;
error:
    return -1;
}

void *stack_pop(stack_t *s)
{
	void *item;
	
    // Empty?
    if (s->numitems == 0)
        goto error;

    // Pop
    s->numitems--;
	item = s->items[s->numitems];
	
	// Zero memory (Thanks to students)
	s->items[s->numitems] = NULL;
    return item;
error:
    return NULL;
}

int stack_size(stack_t *s)
{
    return s->numitems;
}
