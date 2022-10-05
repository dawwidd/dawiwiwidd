#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


void obsluga(int signo)
{
	printf("Odebrano sygnal %d\n", signo);
}


int main(int argc, char* argv[])
{
	signal(SIGINT, obsluga);
	int pid;
	int y=0;


	if((pid=fork())==0)
	{
		while(1)
		{
			y=y^1;
			if(fork()==0)
			{
				(y==0) ? execlp("ps", "ps", NULL) : execlp("ls", "ls", NULL);
				kill(getpid(),9);
			}
		}
	}


	return 0;
}
