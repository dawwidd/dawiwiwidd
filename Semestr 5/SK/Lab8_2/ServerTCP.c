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
    struct sockaddr_in sa;
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
  
    for (;;) {
      int ConnectFD = accept(SocketFD, NULL, NULL);
      fcntl(ConnectFD, F_SETFL, fcntl(ConnectFD, F_GETFL) | O_NONBLOCK);
      if (ConnectFD == -1) {
        perror("accept failed");
        close(SocketFD);
        exit(EXIT_FAILURE);
      }

    char buff[256];
    int n;
    bzero(buff,256);
    n= read(ConnectFD,buff,sizeof(buff));

    printf("message is : %s\n",buff);
    printf("message was %i\n",n);
      /* perform read write operations ... 
      read(ConnectFD, buff, size)
      */
  
      if (shutdown(ConnectFD, SHUT_RDWR) == -1) {
        perror("shutdown failed");
        close(ConnectFD);
        close(SocketFD);
        exit(EXIT_FAILURE);
      }
      close(ConnectFD);
    }

    close(SocketFD);
    return EXIT_SUCCESS;  
}
