#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

int main()
{
	struct msgbuf
	{
		long type;
		char text[1024];
	} my_msg;

	int id = msgget(0x123, 0600 | IPC_CREAT);

	
	strcpy(my_msg.text, "Text\n");
	my_msg.type=5;

	msgsnd(id, &my_msg, strlen(my_msg.text)+1, 0);

	//msgctl(id, IPC_RMID, NULL);

	return 0;
}
