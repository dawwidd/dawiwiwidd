#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>
#include <stdio.h>

int main(int argc, char* argv[]){
	int fd = open(argv[1], O_RDWR);
	char a;
	int check = 1;

	while(read(fd, &a, 1)>0)
	{
		if(!isascii(a))
		{
			check=0;
			break;
		}
	}
	if(check==1) printf("Tak\n");
	else printf("Nie\n");


	close(fd);
}


