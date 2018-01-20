#include "list.h"
#include "common.h"

int main(int argc, char **argv)
{
    list_t *list = list_create(NULL);
    int a[5] = {1,2,3,4};
    list_addfirst(list, a);
    list_addfirst(list, a+1);
    list_addfirst(list, a+2);
    list_addfirst(list, a+3);

 
    return 0;
}
