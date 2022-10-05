#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	mkfifo("kol", 0644);
	int fd1, fd2;

	if(!fork())
	{
		fd1 = open("kol", O_WRONLY);
		dup2(fd1,1);
		execlp("ls", "ls", NULL);
	}
	else
	{
		fd2 = open("kol", O_RDONLY);
		dup2(fd2,0);
		execlp("wc", "wc", NULL);
	}
	
	return 0;
}
