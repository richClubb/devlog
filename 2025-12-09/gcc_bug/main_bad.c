#include <stdio.h>

void set_42(int* p_value)
{
    *p_value = 42;
}

int set_number(void)
{
    // This is the "fix" but this whole code is a bit janky
    // int *p_value = (int *)calloc(1, sizeof(int));
    int *p_value;

    set_42(p_value);

    return *p_value;
}

int main(int argc, char *argv[])
{
    printf("value=%d\n", set_number());
    return 0;
}
