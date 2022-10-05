#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <omp.h>



const int64_t max_threads = 4;
int64_t threads[3] = {4,2,1};

int main() {
	int64_t steps = 1e9;
	double step = 1.0 / steps;

	for (int64_t i = 0; i < 3; i++) {
		printf("thread count = %d\n", threads[i]);
		omp_set_num_threads(threads[i]);
		double t0 = omp_get_wtime();

		volatile double sum[max_threads] = {0};
		#pragma omp parallel
		{
			int64_t id = omp_get_thread_num();
			#pragma omp for
			for (int64_t i = 0; i < steps; i++) {
				double x = (i + 0.5) * step;
				sum[id] += 4.0 / (1.0 + x*x);
			}
		}
		double total = 0;
		for (int64_t i = 0; i < max_threads; i++) total += sum[i];
		double pi = total * step;
		double t1 = omp_get_wtime();

		printf("pi = %.12f\n", pi);
		printf("elapsed %.4f seconds\n", t1-t0);
		printf("---\n");
	}
}
