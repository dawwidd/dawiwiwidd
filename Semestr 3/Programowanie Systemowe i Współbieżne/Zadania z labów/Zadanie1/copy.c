#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>
#include <stdio.h>

int main(int argc, char* argv[]){
	int fd=open(argv[1], O_RDWR);
	int dst=open(argv[2], O_RDWR|O_CREAT, 0644);
	char a;

	while(read(fd, &a, 1) > 0){
		write(dst, &a, 1);
	}
	close(fd);
	close(dst);
}

