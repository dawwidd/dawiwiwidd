#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>


int main()
{
	struct msgbuf
	{
		long type;
		char text[1024];
	} my_msg;

	int id = msgget(0x123, 0600 | IPC_CREAT);

	msgrcv(id, &my_msg, 1024, 5, 0);

	printf("%s", my_msg.text);
	
	//msgctl(id, IPC_RMID, NULL);

	return 0;
}
