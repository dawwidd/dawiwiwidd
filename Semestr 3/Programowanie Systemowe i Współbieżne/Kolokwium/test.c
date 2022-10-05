#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <sys/wait.h>

void handler(int s)
{
    printf("Handler %d\n", s);
    exit(0);
}


void main()
{
    
    int fd= open("testowy", O_WRONLY|O_CREAT, 0600);
    dup2(1,fd);
    write(fd, "adam", 4);
    
}