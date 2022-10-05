#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

int main(int argc, char* argv[])
{
	const char* command = argv[1];
	char* arg_list[argc+1];


	for(int i=1; i<argc; i++)
	{
		arg_list[i-1]=argv[i];
	}
	arg_list[argc]=NULL;
	


	struct timeval tv;

	long start, finish, ustart, ufinish;
	gettimeofday(&tv, NULL);
	start = tv.tv_sec;
	ustart = tv.tv_usec;

	if(fork()==0)
	{
		execvp(command, arg_list);
	}
	wait(0);

	gettimeofday(&tv, NULL);
	finish = tv.tv_sec - start;
	ufinish = tv.tv_usec - ustart;
	printf("%s%d,%d\n", "Czas wykonania: ", finish, ufinish>=0 ? ufinish : 1000000+ufinish);
	
	return 0;
}
