  #include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <unistd.h>
  #include <fcntl.h>
  
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

    if (connect(SocketFD, (struct sockaddr *)&sa, sizeof sa) == -1) {
      perror("connect failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }
    else
    {
        printf("Connection accepted \n");
    }
    
    int n;
    int counter =97;
    char *character;
    for (;;)
    {
      character=&counter;
      n = send(SocketFD,character,1,0);
      
      printf("%d :%d \n",counter,n);
      counter++;
      
      if(counter>122){
        break;
      }
    }
    close(SocketFD);
    return EXIT_SUCCESS;
  }
