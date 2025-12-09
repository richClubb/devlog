#include <stdio.h>
#include <stdlib.h>

void set_42(int* p_value)
{
    *p_value = 42;
}

int set_number(void)
{
    int *p_value = (int *)malloc(1 * sizeof(int));
    set_42(p_value);
    return *p_value;
}

void main(int argc, char **argv)
{
    
    printf("Value=%d\n", set_number());

}