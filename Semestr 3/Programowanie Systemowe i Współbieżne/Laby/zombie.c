#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>

int main()
{
	int status;
	
	if(fork()==0)exit(0);
	if(fork()==0)exit(0);
	if(fork()==0)exit(0);
	sleep(15);
	return 0;
}
