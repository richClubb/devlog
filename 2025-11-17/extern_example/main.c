#include <stdio.h>

// extern is default on function declarations
void do_a_thing();

// it's not on variables. If yuu try to initialise it here you'll get an error
extern int value;

int main(int argc, char **argv)
{

    printf("Value %d\n", value);

    printf("Calling do a thing\n");
    do_a_thing();

    printf("Value %d\n", value);

    return 0;
}