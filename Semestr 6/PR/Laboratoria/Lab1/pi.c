#include <stdio.h>
#include <time.h>
#include <omp.h>

long long num_steps = 1000000000;
double step;

int main(int argc, char* argv[])
{
	clock_t spstart, spstop,ppstart,ppstop;
	
	double sswtime, sewtime, pswtime, pewtime;

    //volatile
	double x, pi, sum=0.0;
	int i;

    //SEKWENCYJNIE
	sswtime = omp_get_wtime();
	spstart = clock();

	step = 1./(double)num_steps;

	for (i=0; i<num_steps; i++)
	{
		x = (i + .5)*step;
		sum = sum + 4.0/(1.+ x*x);
	}
	
	pi = sum*step;

	spstop = clock();
    sewtime = omp_get_wtime();
    printf("%15.12f Wartosc liczby PI sekwencyjnie \n", pi);
  

    //RÓWNOLEGLE 
	pswtime = omp_get_wtime();
	ppstart = clock();
	sum = 0.0;
	step = 1. / (double)num_steps;

    #pragma omp parallel
    #pragma omp for private(x)
	for (i = 0; i < num_steps; i++)
	{
		x = (i + .5) * step;
        #pragma omp atomic
		sum = sum + 4.0 / (1. + x * x);
	}

	pi = sum * step;

	ppstop = clock();
	pewtime = omp_get_wtime();

	printf("%15.12f Wartosc liczby PI rownolegle \n",pi);
	printf("Czas procesorów przetwarzania sekwencyjnego  %f sekund \n", ((double)(spstop - spstart)/CLOCKS_PER_SEC));
	printf("Czas procesorów przetwarzania równoleglego  %f sekund \n", ((double)(ppstop - ppstart)/CLOCKS_PER_SEC));
	printf("Czas trwania obliczen sekwencyjnych - wallclock %f sekund \n",  sewtime-sswtime);
	printf("Czas trwania obliczen rownoleglych - wallclock %f sekund \n", pewtime-pswtime);
	printf("Przyspieszenie %5.3f \n", (sewtime - sswtime) / (pewtime - pswtime));
	return 0;
}
