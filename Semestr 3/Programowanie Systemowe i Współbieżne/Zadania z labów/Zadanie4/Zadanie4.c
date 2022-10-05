#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>
#include <stdio.h>

int main(int argc, char* argv[]){
	int fd=open(argv[1], O_RDWR);
	char a;
	int cnt=0, max=0;

	while(read(fd, &a, 1) > 0){
		if(a=='\n')
		{
			cnt=0;
		}
		else
		{
			cnt+=1;
			if(cnt>max)max=cnt;
		}
	}
	printf("%d\n", max);

	close(fd);
}


