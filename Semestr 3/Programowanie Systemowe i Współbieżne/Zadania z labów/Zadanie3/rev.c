#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	int fd=open(argv[1], O_RDWR);
	int dst=open(argv[2], O_RDWR|O_CREAT, 0644);
	char line[BUFSIZ];
	char a;
	int n = 0;

	while(read(fd, &a, 1) > 0)
	{
		if(&a != "\n")
		{
			printf("%s", a);
			line[n]=a;
			n+=1;
		}
		else
		{
			for(int i = n-1; i >= 0; i--)
			{
				write(dst, &line[i], 1);
			}
			write(dst, "\n", 1);
			n = 0;
		}		
	}
	close(fd);
	close(dst);
}
