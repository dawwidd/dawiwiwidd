#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


void *start_func(void *argument)
{
    printf("Hello World\n");
    sleep(6);
    return NULL;
}


int main()
{
    pthread_t th;
    pthread_create(&th, NULL, start_func, NULL);
    sleep(3);
    pthread_join(th, NULL);
    return 0;
}