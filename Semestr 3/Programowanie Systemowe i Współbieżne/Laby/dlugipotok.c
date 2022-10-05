#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
	mkfifo("kol1", 0644);
	mkfifo("kol2", 0644);
	mkfifo("kol3", 0644);
	mkfifo("kol4", 0644);
	mkfifo("kol5", 0644);

	if(fork()==0)
	{
		int fd1 = open("kol1", O_WRONLY);
		dup2(fd1, 1);
	      	execlp("ps", "ps", "-ef",  NULL);
	}

	if(fork()==0)
	{
		int fd1 = open("kol1", O_RDONLY);
		int fd2 = open("kol2", O_WRONLY);
		dup2(fd1,0);
		dup2(fd2, 1);
	      	execlp("tr", "tr", "-s", "' '", ":",  NULL);
	}

	if(fork()==0)
	{
		int fd2 = open("kol2", O_RDONLY);
		int fd3 = open("kol3", O_WRONLY);

		dup2(fd2,0);
		dup2(fd3, 1);
	      	execlp("cut", "cut", "-d", ":", "-f1", NULL);
	}

	if(fork()==0)
	{
		int fd3 = open("kol3", O_RDONLY);
		int fd4 = open("kol4", O_WRONLY);

		dup2(fd3,0);
		dup2(fd4, 1);
	      	execlp("sort", "sort", NULL);
	}

	if(fork()==0)
	{
		int fd4 = open("kol4", O_RDONLY);
		int fd5 = open("kol5", O_WRONLY);

		dup2(fd4,0);
		dup2(fd5, 1);
	      	execlp("uniq", "uniq", "-c", NULL);
	}
	
	int fd5 = open("kol5", O_RDONLY);

	dup2(fd5,0);
	execlp("sort", "sort", "-n", NULL);

	return 0;
}
