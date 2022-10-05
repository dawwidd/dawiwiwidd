#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>


void opusc(int id, int n)
{
	struct sembuf buf;
	buf.sem_num = n;
	buf.sem_op = -1;
	buf.sem_flg = 0;
	semop(id, &buf, 1);
}

void podnies(int id, int n)
{
	struct sembuf buf;
	buf.sem_num = n;
	buf.sem_op = 1;
	buf.sem_flg = 0;
	semop(id, &buf, 1);
}


int main()
{
	int id;

	id = semget(12345, 6, IPC_CREAT|0644);
	
	short tab[6] = {1,1,1,1,1,4};
	semctl(id, 0, SETALL, tab);

	for(int i=1; i<=5; i++)
	{
		if(fork()==0)
		{
			while(1)
			{
				opusc(id, 5);

				printf("\033[%dm Filozof %d bierze widelec prawy \033[m \n", 31+i, i);
				opusc(id, i%5);

				printf("\033[%dm Filozof %d bierze widelec lewy \033[m \n", 31+i, i);
				opusc(id, (i+1)%5);

				printf("\033[%dm Filozof %d je \033[m \n", 31+i, i);
				sleep(1);

				printf("\033[%dm Filozof %d oddaje widelec lewy \033[m \n", 31+i, i);
				podnies(id, (i+1)%5);

				printf("\033[%dm Filozof %d oddaje widelec prawy \033[m \n", 31+i, i);
				podnies(id, i%5);

				podnies(id, 5);
				sleep(2);
			}
		}
	}

}
