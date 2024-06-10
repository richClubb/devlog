#include <stdio.h>

int main(void)
{
	int a = 10;
	int b = 15;
	int c = 0;

	printf("Control example using intermediate variable\n");
	printf("Initial state -> a: %d, b: %d\n", a, b);

	c = b;
	b = a;
	a = c;
	c = 0;
		
	printf("After swap state -> a: %d, b: %d\n", a, b);

	return 0;
}
