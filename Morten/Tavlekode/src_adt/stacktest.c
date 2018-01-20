/* Author: Aage Kvalnes <aage@cs.uit.no> */
#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

void fatal_error(char *msg)
{
    printf(msg);
    exit(1);
}


int main(int argc, char *argv[])
{
    stack_t *s;
    
    printf("Creating new stack\n");
    s = stack_create();
    if (s == NULL) 
        fatal_error("Stack creation failed\n");

    printf("Pushing items onto stack\n");
	stack_push(s, "one");
	stack_push(s, "two");
	stack_push(s, "three");
    
    printf("Popping items from stack\n");
    while (stack_size(s) > 0) {
        char *item = stack_pop(s);
        printf("Popped item '%s'\n", item);
    }
    printf("Destroying stack\n");
    stack_destroy(s);
    printf("All done\n");
    return 0;
}
