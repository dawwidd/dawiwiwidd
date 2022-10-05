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
	int fd;
	char buf[100]="";
	fd = open("kol", O_RDONLY);

	while(read(fd,buf,100)>0)
	{
		printf("%s", buf);
	}
	
	return 0;
}
