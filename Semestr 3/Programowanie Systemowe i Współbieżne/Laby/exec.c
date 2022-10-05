#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	printf("Begin\n");
	
	if(fork()==0)
	{
		execlp("ps", "ps", "-l", NULL);
	}
	wait(NULL);
	printf("End\n");
	
	return 0;
}
