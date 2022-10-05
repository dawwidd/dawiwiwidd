#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


void *worker(void *info)
{
    execlp("ls", "ls", NULL);
    for(int i=0; i<10; i++)
    {
        sleep(1);
        printf("thread\n");
    }

    return NULL;
}


int main()
{
    pthread_t th;
    
    pthread_create(&th, NULL, worker, NULL);
    
    
    for(int i=0; i<10; i++)
    {
        sleep(1);
        printf("main program\n");
    }

    pthread_join(th, NULL);
    return 0;
}