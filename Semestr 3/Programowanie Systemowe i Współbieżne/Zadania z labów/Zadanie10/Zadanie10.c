#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>
#include <stdio.h>

int main(int argc, char* argv[]){
	int dst=open(argv[argc-1], O_RDWR|O_CREAT, 0644);
	char a;
	int fd;

	for(int i=1; i<argc-1; i++)
	{
		fd=open(argv[i], O_RDWR);
		while(read(fd, &a, 1) > 0){
			write(dst, &a, 1);
		}
		close(fd);
	}
	close(dst);
}

