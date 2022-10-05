#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int main()
{
	struct msgbuf
	{
		long type;
		char text[1024];
	} msg_s, msg_r;

	int id = msgget(0x123, 0600 | IPC_CREAT);

	msgrcv(id, &msg_r, 1024, 1, 0);

	
	for(int i=0; i<strlen(msg_r.text); i++)
	{
		msg_s.text[i]=toupper(msg_r.text[i]);
	}
	msg_s.type=2;

	msgsnd(id, &msg_s, strlen(msg_s.text)+1, 0);
	
	//msgctl(id, IPC_RMID, NULL);

	return 0;
}
