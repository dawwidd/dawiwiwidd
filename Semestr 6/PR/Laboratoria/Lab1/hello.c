#include <stdio.h>
#include <omp.h>

int main() {
	int i;
    #pragma omp parallel
	printf("my id= %d \n", omp_get_thread_num());
	printf("Hello World\n");
	for (i = 0; i < 6; i++)
		printf("Iter:%d\n", i);

	printf("GoodBye World\n");
}