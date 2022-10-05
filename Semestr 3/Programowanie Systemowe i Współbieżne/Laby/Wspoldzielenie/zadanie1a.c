#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>


int main()
{
	int pamiec = shmget(123456, 1024, 0600|IPC_CREAT);
	char* tab;
	
	tab = (char*)shmat(pamiec, NULL, 0);

	while(1)
	{
		strcpy(tab, "Hallo");
		strcpy(tab, "World!!!!!!!!!");	
	}
	return 0;
}
