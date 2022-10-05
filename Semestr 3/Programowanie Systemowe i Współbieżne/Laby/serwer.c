#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	mkfifo("kserwer",0644);

	char buf[8]="";

	int fd = open("kserwer", O_RDONLY);
	read(fd,buf,8);
	fd = open(buf, O_WRONLY);
	dup2(fd,1);
	execlp("ls", "ls", NULL);
	
	return 0;
}
