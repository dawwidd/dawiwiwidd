#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

struct Game_s {
    int active;
    int player1;
    int player2;
    int turn;
    Game_s(): active(0), player1(0), player2(0), turn(0)
    { 
    }
} Games[16];


int findOpponent(int player) {

    for(int i=0; i<16; i++) {
        if(player == Games[i].player1) {
            return Games[i].player2;
        }
        else if(player == Games[i].player2){
            return Games[i].player1;
        }
    }
    return -1;
}

int clearPlayer(int player) {
    for(int i=0; i<16; i++) {
        if(player == Games[i].player1) {
            Games[i].player1 = 0;
            if(Games[i].active == 1) Games[i].active = 0;
            return 1;
        } else if(player == Games[i].player2) {
            Games[i].player2 = 0;
            if(Games[i].active == 1) Games[i].active = 0;
            return 1;
        }
    }
    return 0;
}

void * socketThread(void *arg){
    int newSocket = *((int *)arg);
    int n;
    int col;
    char turn[4];
    int opponentSocket;
    printf("New player %d \n", *((int *)arg));

    for(int i=0; i<16; i++) {
        if(Games[i].active == 0) {
            if(Games[i].player1 == 0) {
                Games[i].player1 = newSocket;
                printf("Player %d joins game %d\n", newSocket, i);
                *((int*) turn) = 0;
                send(newSocket, turn, sizeof(uint32_t), 0);
                Games[i].turn ^= 1;
            } else {
                Games[i].player2 = newSocket;
                printf("Player %d joins game %d\n", newSocket, i);
                *((int*) turn) = 1;
                send(newSocket, turn, sizeof(uint32_t), 0);
                Games[i].turn ^= 1;
            }

            if(Games[i].player1 != 0 && Games[i].player2 != 0) {
                Games[i].active = 1;
                printf("Game %d starts now\n", i);
            }
            break;
        }
    }
    for(;;){
        n=recv(newSocket , &col, sizeof(int), 0);
        printf("%d\n",col);

        if(n<1){
            col = 7;
            if((opponentSocket = findOpponent(newSocket)) == -1) {
                printf("[LOG] Opponent not found\n");
            } else {
                if(send(opponentSocket, &col, sizeof(int), 0) < 0) {
                    printf("[LOG] Failed to send signal\n");
                }
            }
            break;
        }

        if((opponentSocket = findOpponent(newSocket)) == -1) {
            printf("[LOG] Opponent not found\n");
        } else {
            printf("[LOG] Player: %d, Opponent: %d\n", newSocket, opponentSocket);

            if(send(opponentSocket, &col, sizeof(int), 0) < 0) {
                printf("[LOG] Failed to send move\n");
            }
        }
    }
    printf("Player %d left\n", newSocket);

    if( clearPlayer(newSocket) == 0 ) {
        printf("Couldn't remove player %d\n", newSocket);
    }

    pthread_exit(NULL);
}

int main(){
    
    int serverSocket, newSocket;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;

    serverSocket = socket(PF_INET, SOCK_STREAM, 0);
 
    serverAddr.sin_family = AF_INET;
 
    serverAddr.sin_port = htons(1100);

    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);


    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

    if(listen(serverSocket,50)==0) printf("Listening\n");
    else printf("Error\n");

    pthread_t tid[60];
    int i = 0;

    while(1) {
        newSocket = accept(serverSocket, (struct sockaddr *) &serverStorage, &addr_size);

        if( pthread_create(&tid[i++], NULL, socketThread, &newSocket) != 0 ) printf("Failed to create thread\n");

        if( i >= 50) {
            i = 0;

            while(i < 50) {
                pthread_join(tid[i++], NULL);
            }
            i = 0;
        }
    }

    return 0;
}
