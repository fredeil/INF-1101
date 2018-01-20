#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct node {
	struct node *next;
	void *item;
} node_t;

struct stack {
	node_t *head;
	int size;
};

stack_t *stack_create(void) {
	stack_t *s = malloc(sizeof(stack_t));
    if (s == NULL)
        return NULL;
	s->head = NULL;
	s->size = 0;	
	return s;
}

void stack_destroy(stack_t *s) {
	node_t *n, *tmp;
	
	n = s->head;
	while (n != NULL) {
		tmp = n;
		n = n->next;
		free(tmp);
	}
	free(s);
}

int stack_push(stack_t *s, void *item) {
	node_t *n = malloc(sizeof(node_t));
	if (n == NULL)
		return -1;
	n->item = item;
	n->next = s->head;
	s->head = n;
	s->size += 1;
	return 0;
}

void *stack_pop(stack_t *s) {
	void *result;
	node_t *tmp;
	if (s->head == NULL)
		return NULL;
	result = s->head->item;
	tmp = s->head;
	s->head = s->head->next;
	s->size -= 1;
	free(tmp);
	return result;
}

int stack_size(stack_t *s) {
	return s->size;
}

