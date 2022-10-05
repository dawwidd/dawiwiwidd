#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

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
	char a;
	while(read(fd[0], &a, 1)>0)
	{
		printf("%c", toupper(a));
	}
	close(fd[0]);

	return 0;
}
