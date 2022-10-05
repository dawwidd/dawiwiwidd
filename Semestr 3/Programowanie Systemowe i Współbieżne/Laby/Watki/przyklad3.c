#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>


int *worker(void *info)
{
    printf("Argument: %d\n", *(int*)info);
    int *x = malloc(sizeof(int));
    *x = 10;
    return x;
}


int main()
{
    pthread_t th;
    int x = 3;
    pthread_create(&th, NULL, (void *)worker, &x);
    
    int *retVal;
    pthread_join(th, (void **)&retVal);
    
    printf("Return value: %d\n", *retVal);

    free(retVal);
    return 0;
}