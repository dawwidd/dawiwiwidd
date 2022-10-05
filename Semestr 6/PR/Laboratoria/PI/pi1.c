#include <stdio.h>
#include <stdint.h>
#include <omp.h>


int main() {
	int64_t steps = 1e9;
	double step = 1.0 / steps;

	double t0 = omp_get_wtime();
	double x, sum = 0;
	for (int64_t i = 0; i < steps; i++) {
		x = (i + 0.5) * step;
		sum = sum + 4.0 / (1.0 + x*x);
	}
	double pi = sum * step;
	double t1 = omp_get_wtime();

	printf("pi = %.12f\n", pi);
	printf("elapsed %.4f seconds\n", t1-t0);
}
