#include "list.h"
#include "common.h"
#include <string.h>

int main(int argc, char **argv)
{
    char *str1 = "ab";
    char *str2 = "aa";

    if(strcmp(str1, str2) < 0)
    {
        puts("left");
    }

    if(strcmp(str1, str2) > 0)
    {
        puts("right");
    }

    if(strcmp(str1, str2) == 0)
    {
        puts("equal");
    }
    return 0;
}
