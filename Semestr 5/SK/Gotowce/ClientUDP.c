  #include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <unistd.h>

const int one = 1;

int main(int argc, char ** argv){

    struct sockaddr_in serverAdress;

    serverAdress.sin_family = AF_INET;
    serverAdress.sin_port   = htons(1100);
    serverAdress.sin_addr.s_addr  = inet_addr("");
    

    int localSocket = socket(PF_INET, SOCK_DGRAM, 0);
    if (localSocket == -1) {
      perror("cannot create socket");
      exit(EXIT_FAILURE);
    }
    
    char* msg="hello";
    char buff[256];
    int len= sizeof(serverAdress);
    //connect can also be used for UDP, it will set given adress as default
    // if(connect(localSocket,(struct sockaddr 
*)&serverAdress,sizeof(serverAdress))<0)
    // {
    //     close(localSocket);
    //     perror("could not connect");
    // }

    if(sendto(localSocket,(const char*)msg,strlen(msg),0,(const struct sockaddr 
*)&serverAdress,sizeof(serverAdress))<0){
      perror("could not send");
      close(localSocket);
      exit(EXIT_FAILURE);
    }

    if(recvfrom(localSocket,(char*)buff,256,MSG_WAITALL,(struct sockaddr 
*)&serverAdress,&len)<0)
    {
      perror("could not recive");
      close(localSocket);
      exit(EXIT_FAILURE);
    }

    printf("recived: %s\n",buff );

    close(localSocket);

}

