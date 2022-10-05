 #include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <stdio.h>
  #include <stdbool.h>
  #include <stdlib.h>
  #include <string.h>
  #include <unistd.h>
  #include <fcntl.h>
  #include <poll.h>
  
  int main(void)
  {
    struct pollfd poll_set[5];
    struct sockaddr_in sa,ca;
    int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    bool compressPollArr=false;

    if (SocketFD == -1) {
      perror("cannot create socket");
      exit(EXIT_FAILURE);
    }
  
    memset(&sa, 0, sizeof sa);
  
    sa.sin_family = AF_INET;
    sa.sin_port = htons(1100);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

    //fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK)
  
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

    poll_set[0].fd = SocketFD;
    poll_set[0].events = POLLIN;
    int n = 0;
    int currentSize=0;
    int ndfs=1;
    char  buffer[256];

    int len= sizeof(ca);
    for (;;) {

      printf("Wait for poll..\n");
      n =poll(poll_set,ndfs,5000);

      if(n<0)
      {
        perror("poll fail\n");
        break;
      }

       if(n==0)
      {
        printf("poll timeout\n");
        break;
      }

      currentSize=ndfs;

      for(int i=0;i<currentSize;i++){

        if(poll_set[i].revents==0)
        {
          continue;
        }

        if(poll_set[i].revents!=POLLIN)
        {
          break;
        }

        if(poll_set[i].fd==SocketFD)
        {
          for(;;)
          {
            socklen_t ca_size=sizeof(struct sockaddr);
            int ConnectFD = accept(SocketFD, (struct sockaddr *)&ca,&ca_size);
            
            if(ConnectFD<0)
            {
              perror("Connection error");
              break;
            }
            else{
              printf("connected\n");
            }
            
          

            poll_set[ndfs].fd=ConnectFD;
            poll_set[ndfs].events=POLLIN;
            ndfs++;

            if(ConnectFD!=-1)
            {
              break;
            }
          }
        }
        else{

          for(;;)
          {
            printf("Can read \n");

            n=recv(poll_set[i].fd,buffer,sizeof(buffer),0);
            if(n<0)
            {
              break;
            }

            if(n==0)
            {
              printf("Connection closed \n");
              break;
            }

            //do echo
            int len=n;

            n=send(poll_set[i].fd,buffer,n,0);
          }

          close(poll_set[i].fd);
          printf("closing \n");
          poll_set[i].fd=-1;
          compressPollArr=true;
        }
      }

      if( compressPollArr)
      {
        compressPollArr=false;
        for(int i=0;i<ndfs;i++)
        {
          if(poll_set[i].fd==-1)
          {
            for(int j=i;j<ndfs;j++)
            {
              poll_set[j].fd=poll_set[j+1].fd;
            }
            i--;
            ndfs--;
          }
        }
      }

    }

     
    for(int i=0;i<ndfs;i++)
    {
      if(poll_set[i].fd>=0)
        close(poll_set[i].fd);
    }

    close(SocketFD);
    return EXIT_SUCCESS;  
}
