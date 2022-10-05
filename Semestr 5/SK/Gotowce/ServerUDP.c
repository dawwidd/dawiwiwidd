  #include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <unistd.h>

const int one = 1;

char* convertStringCase(char str[],int size){
    char * res;
    res=(char*) malloc(size);
    //toupper
    for(int i=0; i<size; i++){
        res[i]=toupper(str[i]);
        
    }

    printf("res %s \n",res);

    return (char*)res;
}

int main(int argc, char ** argv){
    

    struct sockaddr_in localAddress,clientAdress;

    localAddress.sin_family = AF_INET;
    localAddress.sin_port   = htons(1100);
    localAddress.sin_addr.s_addr  = htonl(INADDR_ANY);
    
    
    int server_socket = socket(PF_INET, SOCK_DGRAM, 0);

    if (server_socket == -1) {
      perror("cannot create socket");
      exit(EXIT_FAILURE);
    }
    
    
    
    if(bind(server_socket, (struct sockaddr*) &localAddress, 
sizeof(localAddress))==-1)
    {
        perror("Could not bind");
        close(server_socket);
    }
       
    int n;
    int len= sizeof(clientAdress);
    char buff[256];

    
    for(;;) {
      
        //read
        if(recvfrom(server_socket,(char*)buff,256,MSG_WAITALL,(struct sockaddr 
*)&clientAdress,&len)<0)
        {
            perror("could not recive");
            close(server_socket);
            exit(EXIT_FAILURE);
        }
        printf("recived  message: %s ,sending response\n",buff);
 
        //write
        if(sendto(server_socket,"hello",6,0,(const struct sockaddr 
*)&clientAdress,len)<0)
        {
            perror("could not send");
            close(server_socket);
            exit(EXIT_FAILURE);
        }
        

    }

    close (server_socket);
}

