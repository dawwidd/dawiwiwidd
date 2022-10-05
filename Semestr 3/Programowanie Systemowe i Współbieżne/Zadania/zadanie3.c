#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int fd[2];
	pipe(fd);

	if(fork()==0)
	{
		close(fd[0]);
		write(fd[1], "Hello\n", 7);
		close(fd[1]);
		exit(0);
	}
	else
	{
		if(fork()==0)
		{
			close(fd[0]);
			write(fd[1], "World\n", 7);
			close(fd[1]);
			exit(1);
		}
		else
		{
			char a;
			close(fd[1]);
			while(read(fd[0], &a, 1)>0) printf("%c", a);
			close(fd[0]);
		}	
	}

	return 0;
}
