#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int fd[2];
	int fd1[2];

	pipe(fd);
	pipe(fd1);
	
	if(fork()==0)
	{
		close(fd[0]);
		close(fd1[0]);
		close(fd1[1]);
		dup2(fd[1], 1);
	      	execlp("ls", "ls", "-l", NULL);
		exit(0);
	}
	else
	{
		if(fork()==0)
		{
			close(fd[1]);
			close(fd1[0]);
			dup2(fd[0],0);
			dup2(fd1[1],1);
			execlp("grep", "grep", "^d", NULL);
			exit(1);
		}
		close(fd[0]);
		close(fd[1]);
		close(fd1[1]);
		dup2(fd1[0],0);
		execlp("more", "more", NULL);
		close(fd1[0]);
	}

	return 0;
}
