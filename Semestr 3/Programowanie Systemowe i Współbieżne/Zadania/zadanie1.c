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
		write(fd[1], "Hallo", 6);
		close(fd[1]);
	}
	else
	{
		char buf[10];
		read(fd[0], buf, 10);
		close(fd[0]);
		printf("Odczytano z potoku: %s\n", buf);
	}


	return 0;
}
