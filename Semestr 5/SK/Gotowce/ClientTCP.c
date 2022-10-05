  #include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <unistd.h>
  
  int main(int argc, char *argv[])
  {
    struct sockaddr_in sa;
    int res;
    int SocketFD;
    int port=atoi(argv[2]);
    printf ("addr: %s\n",argv[1]);
    printf ("port: %i\n",port);
    SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (SocketFD == -1) {
      perror("cannot create socket");
      exit(EXIT_FAILURE);
    }
    
    memset(&sa, 0, sizeof sa);
    
    sa.sin_addr.s_addr=inet_addr(argv[1]);
    sa.sin_family = AF_INET;
    
    sa.sin_port = htons(port);
    //res = inet_aton(AF_INET, "192.168.100.83", &sa.sin_addr);
   
    if (connect(SocketFD, (struct sockaddr *)&sa, sizeof sa) == -1) {
      perror("connect failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }
    else
    {
        printf("Connection accepted \n");
    }
    
    char buff[256];
    bzero(buff,256);
    fgets(buff,255,stdin);
    int n;

    n = write(SocketFD,buff,strlen(buff));
    /* perform read write operations ... */
  
    close(SocketFD);
    return EXIT_SUCCESS;
  }
