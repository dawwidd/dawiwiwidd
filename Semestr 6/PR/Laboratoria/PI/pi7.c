#include <stdio.h>
#include <stdint.h>
#include <omp.h>

typedef uint64_t u64;
typedef int64_t  i64;
typedef double   f64;

int main() {
	int64_t steps = 1e9;
	double step = 1.0 / steps;

	omp_set_num_threads(2);
	const int64_t runs = 50;
	volatile double sum[runs];

	for (int64_t k = 0; k < runs-1; k++) {
		sum[k] = 0;
		sum[k+1] = 0;

		double t0 = omp_get_wtime();
		#pragma omp parallel
		{
			int64_t id = omp_get_thread_num();
			#pragma omp for
			for (int64_t i = 0; i < steps; i++) {
				double x = (i + 0.5) * step;
				sum[k+id] += 4.0 / (1.0 + x*x);
			}
		}
		double t1 = omp_get_wtime();
		double pi = (sum[k]+sum[k+1])*step;
		printf("elapsed %.4f seconds (run %d)\n", t1-t0, k);
	}
}
