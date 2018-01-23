#include "lib/tap.h"
#include "../list.h"

int string_compare(void *p1, void *p2)
{
   return strcasecmp((char*)p1, (char*)p2);
}

int main () 
{
    plan(12);

    list_t *list = list_create(string_compare);

    // List create
    ok(list != NULL, "list_create");

    // List size
    ok(list_size(list) == 0, "list_size");

    // Addfirst
    list_addfirst(list, "b");
    ok(list_size(list) == 1, "list_addfirst");

    // Contains
    ok(list_contains(list, "b"), "list_contains");

    // Addlast
    list_addlast(list, "a");
    ok(list_size(list) == 2, "list_addlast");

    // List poplast
    ok(strcmp((char*)list_poplast(list), "a") == 0, "list_poplast");

    // List popfirst
    ok(strcmp((char*)list_popfirst(list), "b") == 0, "list_popfirst");

    // List sort
    list_addfirst(list, "a");
    list_addfirst(list, "b");
    list_sort(list);
    ok(strcmp((char*)list_popfirst(list), "a") == 0, "list_sort");

    list_destroy(list);

    /*** Iterator tests ****/
    list = list_create(NULL);
    list_addfirst(list, "a");
    list_addfirst(list, "b");

    // Create
    list_iter_t *iter = list_createiter(list);
    ok(iter != NULL, "list_createiter");

    // Hasnext
    ok(list_hasnext(iter), "list_hasnext");

    // Next
    ok(strcmp((char*)list_next(iter), "b") == 0, "list_next");

    list_destroyiter(iter);

    // Next/hasnext
    iter = list_createiter(list);
    int expected = 2;
    int actual = 0;

    while(list_hasnext(iter)) 
    {
        list_next(iter);
        actual++;
    }

    ok(expected == actual, "next/hasnext");

    list_destroy(list);
    list_destroyiter(iter);

    done_testing();
}