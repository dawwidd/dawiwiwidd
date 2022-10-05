#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char* argv[])
{
	mkfifo("kserwer",0644);

	char name[] = "kclient";

	mkfifo(name,0644);

	int fd = open("kserwer", O_WRONLY);
	write(fd,name,8);
	close(fd);

	char buf[1024]="";
	fd = open(name, O_RDONLY);
	int x;
	while((x=read(fd,buf,8))>0)
	{
		printf("%s",buf);
		strcpy(buf," ");
	}
	
	return 0;
}
