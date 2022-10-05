#include <stdio.h>
#include <time.h>
#include <omp.h>

long int NUM_STEPS = 1000000000;


void pi1() {
    double step = 1.0/(double)NUM_STEPS;
    double x;
    double sum = 0;
    double pi;
    double startTime = omp_get_wtime();

    for(long int i = 0; i < NUM_STEPS; i++) {
        x = (i + 0.5)*step;
        sum = sum + 4.0/(1.0+x*x);
    }
    pi = sum*step;

    double stopTime = omp_get_wtime();

    printf("ZADANIE 1:\n");
    printf("Wartość liczby PI sekwencyjnie: %.12f\n", pi);
    printf("Czas: %.4f s\n", stopTime-startTime);
}

void pi2() {
    int numOfThreads[3] = {8, 4, 2};

    printf("\nZADANIE 2:\n");
    for(int i = 0; i < 3; i++) {
        printf("Liczba wątków: %d\n", numOfThreads[i]);
        omp_set_num_threads(numOfThreads[i]);

        double step = 1.0/(double)NUM_STEPS;
        double x;
        double sum = 0;
        double pi;
        double startTime = omp_get_wtime();

        #pragma omp parallel for
        for(long int i = 0; i < NUM_STEPS; i++) {
            x = (i + 0.5)*step;
            sum = sum + 4.0/(1.0+x*x);
        }
        pi = sum*step;

        double stopTime = omp_get_wtime();

        printf("Wartość liczby PI: %.12f\n", pi);
        printf("Czas: %.4f s\n\n", stopTime-startTime);
    }
}

void pi3() {
    int numOfThreads[3] = {8, 4, 2};

    printf("\nZADANIE 3:\n");
    for(int i = 0; i < 3; i++) {
        printf("Liczba wątków: %d\n", numOfThreads[i]);
        omp_set_num_threads(numOfThreads[i]);

        double step = 1.0/(double)NUM_STEPS;
        double x;
        double sum = 0;
        double pi;
        double startTime = omp_get_wtime();

        #pragma omp parallel for
        for(long int i = 0; i < NUM_STEPS; i++) {
            x = (i + 0.5)*step;
            #pragma omp atomic
            sum = sum + 4.0/(1.0+x*x);
        }
        pi = sum*step;

        double stopTime = omp_get_wtime();

        printf("Wartość liczby PI: %.12f\n", pi);
        printf("Czas: %.4f s\n\n", stopTime-startTime);
    }
}

void pi4() {
    int numOfThreads[3] = {8, 4, 2};

    printf("\nZADANIE 4:\n");
    for(int i = 0; i < 3; i++) {
        printf("Liczba wątków: %d\n", numOfThreads[i]);
        omp_set_num_threads(numOfThreads[i]);

        double step = 1.0/(double)NUM_STEPS;
        double sum = 0;
        double pi;
        double startTime = omp_get_wtime();

        #pragma omp parallel
        {
            double sumLocal = 0;
            #pragma omp for
            for(long int i=0; i < NUM_STEPS; i++) {
                double x = (i + 0.5) * step;
                sumLocal += 4.0 / (1.0 + x*x);
            }
            #pragma omp atomic
            sum += sumLocal;
        }
        
        pi = sum*step;

        double stopTime = omp_get_wtime();

        printf("Wartość liczby PI: %.12f\n", pi);
        printf("Czas: %.4f s\n\n", stopTime-startTime);
    }
}

void pi5() {
    int numOfThreads[3] = {8, 4, 2};

    printf("\nZADANIE 5:\n");
    for(int i = 0; i < 1; i++) {
        printf("Liczba wątków: %d\n", numOfThreads[i]);
        omp_set_num_threads(numOfThreads[i]);

        double step = 1.0/(double)NUM_STEPS;
        double sum = 0;
        double pi;
        double startTime = omp_get_wtime();

        #pragma omp parallel for reduction(+: sum)
        for(long int i=0; i < NUM_STEPS; i++) {
            double x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x*x);
        }
        
        pi = sum*step;

        double stopTime = omp_get_wtime();

        printf("Wartość liczby PI: %.12f\n", pi);
        printf("Czas: %.4f s\n\n", stopTime-startTime);
    }
}

void pi6() {
    int numOfThreads[3] = {8, 4, 2};

    printf("\nZADANIE 6:\n");
    for(int i = 0; i < 3; i++) {
        printf("Liczba wątków: %d\n", numOfThreads[i]);
        omp_set_num_threads(numOfThreads[i]);

        double step = 1.0/(double)NUM_STEPS;
        double sum = 0;
        volatile double localSums[8] = {0};
        double pi;
        double startTime = omp_get_wtime();

        #pragma omp parallel
        {
            int threadNum = omp_get_thread_num();
            #pragma omp for
            for(long int i=0; i < NUM_STEPS; i++) {
                double x = (i + 0.5) * step;
                localSums[threadNum] += 4.0 / (1.0 + x*x);
            }
        }
        for(int i = 0; i < 8; i++) {
            sum += localSums[i];
        }
        
        pi = sum*step;

        double stopTime = omp_get_wtime();

        printf("Wartość liczby PI: %.12f\n", pi);
        printf("Czas: %.4f s\n\n", stopTime-startTime);
    }
}

void pi7() {

    printf("\nZADANIE 7:\n");
    printf("Liczba wątków: 2\n");
    omp_set_num_threads(2);

    double step = 1.0/(double)NUM_STEPS;
    int numOfIterations = 50;
    volatile double sum[50];
    double pi;

    for (int i = 0; i < numOfIterations-1; i++)
    {
        sum[i] = 0;
        sum[i+1] = 0;

        double startTime = omp_get_wtime();
        #pragma omp parallel
        {
            int threadNum = omp_get_thread_num();
            #pragma omp for
            for(long int k=0; k < NUM_STEPS; k++) {
                double x = (k + 0.5) * step;
                sum[i+threadNum] += 4.0 / (1.0 + x*x);
            }
        }
        
        pi = (sum[i]+sum[i+1])*step;

        double stopTime = omp_get_wtime();

        printf("Iteracja: %d\n", i);
        printf("Wartość liczby PI: %.12f\n", pi);
        printf("Czas: %.4f s\n\n", stopTime-startTime);
    }
    
}

int main(int argc, char* argv[])
{
	pi1();
    // pi2();
    // pi3();
    // pi4();
    // pi5();
    // pi6();
    // pi7();
	return 0;
}
