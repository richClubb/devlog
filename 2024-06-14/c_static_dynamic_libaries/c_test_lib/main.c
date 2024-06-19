#include <stdio.h>
#include "add_lib.h"

void main(void)
{
	int result = 0;

	printf("Adding\n");

	result = add(10, 56);

	printf("Result %d\n", result);

	return;
}
