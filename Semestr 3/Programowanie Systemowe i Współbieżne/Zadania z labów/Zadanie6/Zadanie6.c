#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>
#include <stdio.h>

int main(int argc, char* argv[]){
	int fd = open(argv[1], O_RDWR);
	int dst= open(argv[2], O_RDWR|O_CREAT, 0644);
	char a;
	int count=0;

	lseek(fd, -10, SEEK_END);

	while(read(fd, &a, 1) > 0){
		write(dst, &a, 1);
	}

	while(count<10)
	{
		lseek(fd, -1, SEEK_CUR);
		if(read(fd, &a, 1)>0 && isspace(a))
		{
			count+=1;
		}
		lseek(fd, -1, SEEK_CUR);
	}
	lseek(fd, 1, SEEK_CUR);
	while(read(fd, &a, 1)>0)
	{
		write(dst, &a, 1);
	}

	count = 0;

	while(count<10)
	{
		lseek(fd, -1, SEEK_CUR);
		if(read(fd, &a, 1)>0 && a=='\n')
		{
			count+=1;
		}
		lseek(fd, -1, SEEK_CUR);
	}

	while(read(fd, &a, 1)>0)
	{
		write(dst, &a, 1);
	}


	
	close(dst);
	close(fd);
}


