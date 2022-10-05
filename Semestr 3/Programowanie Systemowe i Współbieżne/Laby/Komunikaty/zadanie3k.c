#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	struct msgbuf
	{
		long type;
		char text[1024];
	} msg_s, msg_r;

	int id = msgget(0x123, 0600 | IPC_CREAT);

	strcpy(msg_s.text, argv[1]);
	msg_s.type=1;
	
	msgsnd(id, &msg_s, strlen(msg_s.text)+1, 0);

	msgrcv(id, &msg_r, 1024, 2, 0);
	printf("%s\n", msg_r.text);

	//msgctl(id, IPC_RMID, NULL);

	return 0;
}
