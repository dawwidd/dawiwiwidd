#include <stdio.h>
#include <omp.h>

int main() {
	int i = 0;
	int j = 0;
	omp_set_num_threads(4);
#pragma omp parallel num_threads(5)
	{
	int id = omp_get_thread_num();
	printf("Hello World %d\n", i);
	#pragma omp for schedule(static)
	for (i = 0;  i< 15; i++)
		printf('Iter:%d, thread : %d \n', i, id);
	}
	printf("GoodBye World \n");
}