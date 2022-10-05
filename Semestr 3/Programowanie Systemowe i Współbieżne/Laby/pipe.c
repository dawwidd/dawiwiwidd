#include <stdio.h>
#include <unistd.h>

int main()
{
	int fd[2];

	pipe(fd);
	
	if(fork()==0)
	{
		close(fd[0]);
		write(fd[1], "Hello", 5);
		close(fd[1]);
	}
	else
	{
		char buf[5];
		close(fd[1]);
		while(read(fd[0], buf, 5)) printf("%s\n", buf);
	}

	return 0;
}
