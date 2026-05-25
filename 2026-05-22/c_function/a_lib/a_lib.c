#include "a_lib.h"

#include <stdio.h>

int a_weird_global = 0;

int a_function(void) {
    printf("This is a thing\n");
    return a_weird_global++;  
}