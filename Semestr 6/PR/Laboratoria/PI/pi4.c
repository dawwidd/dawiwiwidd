#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <omp.h>


int64_t threads[3] = {8,4,1};

int main() {
	int64_t steps = 1e9;
	double step = 1.0 / steps;

	for (int64_t i = 0; i < 3; i++) {
		printf("thread count = %d\n", threads[i]);
		omp_set_num_threads(threads[i]);
		double t0 = omp_get_wtime();

		double sum = 0;
		#pragma omp parallel
		{
			double local_sum = 0;
			#pragma omp for
			for (int64_t i = 0; i < steps; i++) {
				double x = (i + 0.5) * step;
				local_sum += 4.0 / (1.0 + x*x);
			}
			#pragma omp atomic
			sum += local_sum;
		}
		double pi = sum * step;
		double t1 = omp_get_wtime();

		printf("pi = %.12f\n", pi);
		printf("elapsed %.4f seconds\n", t1-t0);
		printf("---\n");
	}
}
