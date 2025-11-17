#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

void return_func(int a)
{
	printf("wtf\n");
}

void check_func(int a)
{
	if (a <= 0) assert(false);

	printf("Yay '%d'\n", a);
}

// here's the declaration `void (*signal(int, void (*fp)(int)))(int);`
void (*signal(int, void (*fp)(int)))(int)
{
	fp(a);

	printf("result %d\n", 10 / a);

	return &return_func;
}

int main(int argc, char **argv)
{
	
	void (*fp)(int);

	fp = &check_func;

	void (*a_func)(int);

	a_func = signal(1, fp);

	a_func(1);

	return 0;
}
