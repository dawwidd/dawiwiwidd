#include <signal.h>
#include <stdio.h>
#include <unistd.h>


void obsluga(int signo)
{
	printf("Odebrano sygnal %d\n", signo);
}


int main(int argc, char* argv[])
{
	//signal(SIGINT, obsluga);
	
	signal(SIGINT, SIG_IGN);

	while(1)
	{
		printf("waiting for signal\n");
		sleep(1);
	}


	return 0;
}
