#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int fd1[2];
	int fd2[2];
	int fd3[2];
	pipe(fd1);
	pipe(fd2);
	pipe(fd3);
	
	int tab[4] = {1,2,3,4};

	if(fork()==0)
	{
		close(fd1[0]);
		for(int i=0; i<4; i++)
		{
			write(fd1[1], tab+i, sizeof(int));
		}
		close(fd1[1]);
		exit(0);
	}
	else
	{
		if(fork()==0)
		{
			for(int i=0; i<4; i++)
			{
				read(fd1[0], tab+i, sizeof(int));
				tab[i]+=1;
			}
			close(fd1[0]);

			for(int i=0; i<4; i++)
			{
				write(fd2[1], tab+i, sizeof(int));
			}
			close(fd2[1]);
			exit(1);
		}
		else
		{
			if(fork()==0)
			{
				for(int i=0; i<4; i++)
				{
					read(fd2[0], tab+i, sizeof(int));
					tab[i]+=1;
				}
				close(fd2[0]);
	
				for(int i=0; i<4; i++)
				{
					write(fd3[1], tab+i, sizeof(int));
				}
				close(fd3[1]);
				exit(2);
			}
			else
			{
				for(int i=0; i<4; i++)
				{
					read(fd3[0], tab+i, sizeof(int));
					tab[i]+=1;
				}
				close(fd3[0]);
				printf("%d, %d, %d, %d\n", tab[0], tab[1], tab[2], tab[3]);
			}
	
		}
	}

	return 0;
}
