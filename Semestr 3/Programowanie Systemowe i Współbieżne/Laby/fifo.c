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
		write(fd1, "Hello\n",7);
	}
	else
	{
		char buf[100]="";
		fd2 = open("kol", O_RDONLY);

		while(read(fd2,buf,100)>0)
		{
			printf("%s", buf);
		}
	}
	
	return 0;
}
