#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int fd[2];
	int fd1[2];
	int fd2[2];
	int fd3[2];
	int fd4[2];

	pipe(fd);
	if(fork()==0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
	      	execlp("ps", "ps", "-ef",  NULL);
		exit(0);
	}
	close(fd[1]);

	pipe(fd1);
	if(fork()==0)
	{
		close(fd1[0]);
		dup2(fd[0],0);
		dup2(fd1[1], 1);
	      	execlp("tr", "tr", "-s", "' '", ":",  NULL);
		exit(0);
	}
	close(fd1[1]);

	pipe(fd2);
	if(fork()==0)
	{
		close(fd2[0]);
		dup2(fd1[0],0);
		dup2(fd2[1], 1);
	      	execlp("cut", "cut", "-d", ":", "-f1", NULL);
		exit(0);
	}
	close(fd2[1]);

	pipe(fd3);
	if(fork()==0)
	{
		close(fd3[0]);
		dup2(fd2[0],0);
		dup2(fd3[1], 1);
	      	execlp("sort", "sort", NULL);
		exit(0);
	}
	close(fd3[1]);

	pipe(fd4);
	if(fork()==0)
	{
		close(fd4[0]);
		dup2(fd3[0],0);
		dup2(fd4[1], 1);
	      	execlp("uniq", "uniq", "-c", NULL);
		exit(0);
	}
	close(fd4[1]);

	dup2(fd4[0],0);
	execlp("sort", "sort", "-n", NULL);

	return 0;
}
