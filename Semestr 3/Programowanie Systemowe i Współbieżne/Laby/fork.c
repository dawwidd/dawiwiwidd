#include <stdio.h>
#include <unistd.h>

int main()
{
	fork();
	printf("Hi\n");
	fork();
	printf("Ha\n");
	fork();
	printf("Ho\n");

	return 0;
}
