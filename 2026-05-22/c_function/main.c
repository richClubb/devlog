#include <stdio.h>

#include "a_lib.h"

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    printf("%d\n", a_function());
    printf("%d\n", a_function());
}