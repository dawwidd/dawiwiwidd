#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/sem.h>


void opusc(int id, int n)
{
	struct sembuf buf;
	buf.sem_num=n;
	buf.sem_op=-1;
	buf.sem_flg=0;
	semop(id, &buf, 1);
}

void podnies(int id, int n)
{
	struct sembuf buf;
	buf.sem_num=n;
	buf.sem_op=1;
	buf.sem_flg=0;
	semop(id, &buf, 1);
}


int main()
{
	int sid = semget(111111, 1, 0644|IPC_CREAT);
	semctl(sid, 0, SETVAL, 1);

	int pamiec = shmget(123456, 1024, 0600|IPC_CREAT);
	char* tab;
	
	tab = (char*)shmat(pamiec, NULL, 0);

	while(1)
	{
		opusc(sid,0);
		strcpy(tab, "Hallo");
		podnies(sid,0);
		opusc(sid,0);
		strcpy(tab, "World!!!!!!!!!");
		podnies(sid,0);
	}
	return 0;
}
