#include <stdio.h>
#include <pthread.h>


struct argumenty
{
    char znak;
    int licznik;
};

void *drukuj_znak(void *arg)
{
    struct argumenty *p = (struct argumenty*) arg;
    int i;
    for(int i = 0; i < p->licznik; ++i)
    {
        fputc(p->znak, stderr);
    }
    return NULL;
}


int main()
{
    pthread_t th1;
    pthread_t th2;
    
    struct argumenty th1_arg;
    struct argumenty th2_arg;
    
    th1_arg.znak = 'x';
    th1_arg.licznik = 
    
    printf("Return value: %d\n", *retVal);

    free(retVal);
    return 0;
}