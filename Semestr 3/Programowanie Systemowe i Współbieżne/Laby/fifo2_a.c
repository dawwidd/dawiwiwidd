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
	fd = open("kol", O_WRONLY);
	write(fd, "Hello\n",7);
	
	return 0;
}
