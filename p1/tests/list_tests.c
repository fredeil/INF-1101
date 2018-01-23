#include "tap.h"
#include "../list.h";

int main () 
{
    plan(1);
    ok(50 + 5, "foo %s", "bar");
    done_testing();
}