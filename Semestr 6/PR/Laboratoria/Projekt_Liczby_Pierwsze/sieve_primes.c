#include <stdio.h>
#include <time.h>
#include <omp.h>
#include <stdlib.h>
#include <math.h>

#define llint unsigned long long int

int main(int argc, char* argv[]) {
    llint min = atoll(argv[1]);
    llint max = atoll(argv[2]);
    llint maxSqrt = (llint)sqrt(max);
    llint *primes = malloc(sizeof(llint) * max);
    llint numOfPrimes = 0;
    llint numOfPrimesInFirstRow = 0;
    double startTime;
    double stopTime;

    startTime = omp_get_wtime();
    char* sieve = malloc(sizeof(char) * max);
    for (llint i = 2; i <= max; sieve[i++]=1);
    
    for(llint i = 2; i <= maxSqrt; i++) {
        if(sieve[i] == 1) {
            primes[numOfPrimesInFirstRow] = i;
            numOfPrimesInFirstRow++;
            for (llint j = 2*i; j <= maxSqrt; j += i)
            {
                sieve[j] = 0;
            }
        }
    }
    printf("Number of primes in first row: %lld\n", numOfPrimesInFirstRow);

    for (llint i = 0; i < numOfPrimesInFirstRow; i++)
    {
        for (llint j = 2; j*primes[i] <= max; j++)
        {
            sieve[j*primes[i]] = 0;
        }
        
    }

    llint lineCounter = 0;
    for(llint i = min; i <= max; i++) {
        if(sieve[i] == 1) {
            numOfPrimes++;

            if(atoi(argv[3]) == 1) {
                printf("%lld, ", i);
            }
            lineCounter++;
        }

        if(lineCounter == 10) {
            lineCounter = 0;

            if(atoi(argv[3]) == 1) {
                printf("\n");
            }
        }
    }

    stopTime = omp_get_wtime();
    printf("\n");
    printf("Number of primes: %lld\n", numOfPrimes);
    printf("Time: %g\n", stopTime-startTime);
    
    return 0;
}
