#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int fd[2];

	pipe(fd);
	
	if(fork()==0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
	      	execlp("ls", "ls", NULL);
		close(fd[1]);
		exit(0);
	}
	close(fd[1]);
	dup2(fd[0], 0);
	execlp("wc", "wc", NULL);
	close(fd[1]);

	return 0;
}
