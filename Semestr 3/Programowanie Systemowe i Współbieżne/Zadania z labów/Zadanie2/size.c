#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/stat.h>

int main(int argc, char* argv[]){

	struct stat st;
	int size;
	for(int i=1; i<argc; i++){
		int fd=open(argv[i], O_RDWR);
		size = lseek(fd, 0, SEEK_END);
		printf("%d\n", size);
	}	
}
