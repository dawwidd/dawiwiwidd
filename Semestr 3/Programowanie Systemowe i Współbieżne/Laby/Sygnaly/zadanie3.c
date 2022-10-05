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
	signal(SIGALRM, obsluga);
	int pid;

	alarm(atoi(argv[1]));

	if((pid=fork())==0)
	{
		char x[20];
		while(1)
		{
			scanf("%s", x);
			if(fork()==0)
			{
				execlp(x,x,NULL);
				kill(getpid(),9);
			}
		}
	}
	else
	{
		pause();
		kill(pid, 9);
	}


	return 0;
}
