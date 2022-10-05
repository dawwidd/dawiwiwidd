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
	} my_msg;

	int id = msgget(0x123, 0600 | IPC_CREAT);

	for(int i=1; i<=atoi(argv[1]); i++)
	{
	strcpy(my_msg.text, "Text\n");
	my_msg.type=i;
	
	msgsnd(id, &my_msg, strlen(my_msg.text)+1, 0);
	}

	//msgctl(id, IPC_RMID, NULL);

	return 0;
}
