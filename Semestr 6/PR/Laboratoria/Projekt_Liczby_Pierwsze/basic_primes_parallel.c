#include <stdio.h>
#include <time.h>
#include <omp.h>
#include <stdlib.h>
#include <math.h>

#define llint unsigned long long int

int checkPrimeBasic(llint x) {
    llint sqrtX = (int)sqrt(x);

    if(x % 2 == 0) {
        return 0;
    }

    for (llint i = 3; i <= sqrtX; i++)
    {
        if(x % i == 0) {
            return 0;
        }
    }
    return 1;    
}

llint getPrimesLowerThanSqrtOfNumber(llint x, llint* primes) {
    llint sqrtOfNum = (int)sqrt(x);

    primes[0] = 2;
    int numOfPrimes = 1;
    for (llint i = 3; i <= sqrtOfNum; i+=2)
    {  
        if(checkPrimeBasic(i)) {
            primes[numOfPrimes] = i;
            // printf("%lld\n", i);
            numOfPrimes++;
        }
    }

    return numOfPrimes;
}


int checkPrime(llint x, llint* primes, llint numOfPrimes) {
    llint sqrtX = (llint)sqrt(x);


    if(x == 1) {
        return 0;
    }

    if(x % 2 == 0 && x != 2) {
        return 0;
    }

    for (llint i = 0; i < numOfPrimes; i++)
    {
        if(primes[i] > sqrtX) {
            break;
        }
        if(x % primes[i] == 0) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char* argv[]) {
    
    llint min = atoll(argv[1]);
    llint max = atoll(argv[2]);
    llint numOfPrimesForSearching = 0;
    llint numOfPrimes = 0;
    llint numOfPrimesInBetween = 0;
    llint* primes = malloc(sizeof(llint) * max);
    

    numOfPrimesForSearching = getPrimesLowerThanSqrtOfNumber(max, primes);
    printf("Number of primes after 1st iteration: %lld\n", numOfPrimesForSearching);

    int* isPrime = malloc(sizeof(int) * (max-min));

    omp_set_num_threads(8);
    #pragma omp parallel for
    for (llint i = min; i <= max; i++)
    {
        if(checkPrime(i, primes, numOfPrimesForSearching)) {
            isPrime[i-min] = 1;
        }
        else {
            isPrime[i-min] = 0;
        }
    }

    llint lineCounter = 0;
    for (llint i = min; i <= max; i++)
    {
        if(isPrime[i-min] == 1) {
            numOfPrimesInBetween++;

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
    printf("\n");
    printf("Primes found between %lld-%lld: %lld\n", min, max, numOfPrimesInBetween);

    free(primes);
    free(isPrime);
    return 0;
}
