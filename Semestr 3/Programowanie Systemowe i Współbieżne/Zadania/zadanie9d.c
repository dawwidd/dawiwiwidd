#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
	int fd[2];
	int fd1[2];

	pipe(fd);
	if(fork()==0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
	      	execlp("cat", "cat", "/etc/group",  NULL);
		exit(0);
	}
	close(fd[1]);

	pipe(fd1);
	if(fork()==0)
	{
		close(fd1[0]);
		dup2(fd[0],0);
		dup2(fd1[1], 1);
	      	execlp("head", "head", "-5", NULL);
		exit(0);
	}
	close(fd1[1]);

	dup2(fd1[1],1);
	
	char a;
	int plik=open("grupy.txt", O_RDWR|O_CREAT, 0644);
	while(read(fd[1], &a, 1)>0)
	{
		write(plik,&a,1);
	}
	close(plik);

	return 0;
}
