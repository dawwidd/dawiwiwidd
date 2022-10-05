 #include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <unistd.h>
  #include <fcntl.h>
  
  int main(void)
  {
    struct sockaddr_in sa,ca;
    int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (SocketFD == -1) {
      perror("cannot create socket");
      exit(EXIT_FAILURE);
    }
  
    memset(&sa, 0, sizeof sa);
  
    sa.sin_family = AF_INET;
    sa.sin_port = htons(1100);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(SocketFD,(struct sockaddr *)&sa, sizeof sa) == -1) {
      perror("bind failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }
  
    if (listen(SocketFD, 10) == -1) {
      perror("listen failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }
  int len= sizeof(ca);

  for (;;) {
    socklen_t ca_size=sizeof(struct sockaddr);
    int ConnectFD = accept(SocketFD, (struct sockaddr *)&ca,&ca_size);

    if (ConnectFD == -1) {
      perror("accept failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }

   
    int n=1;
    for (;;){
      if (n>0)
      { 
          int msgSize=0;
          n= recv(ConnectFD,&msgSize,sizeof(msgSize),MSG_WAITALL);

          char buff[htonl(msgSize)];

          n= recv(ConnectFD,buff,htonl(msgSize),MSG_WAITALL);
          printf("%d : %s\n",n,buff);

          memset(&buff, 0, sizeof (buff));
      }
      else{
          printf("message was %i\n",n);
          break;
      }

    }
      close(ConnectFD);
    }

    close(SocketFD);
    return EXIT_SUCCESS;  
}
