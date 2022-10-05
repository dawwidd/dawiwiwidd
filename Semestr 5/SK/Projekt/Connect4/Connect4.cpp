#include <SFML/Graphics.hpp>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h> 
#include <pthread.h>
#include <vector>

using namespace std;
using namespace sf;

const int WIDTH = 7;
const int HEIGHT = 6;

int board[HEIGHT][WIDTH];
int columnMax[WIDTH];
int counter;
int j = 0;
int k = 0;
int turn;
char myTurn[4];
char msg[4];
int firstTurn = 0;
int col;
bool firstTime;

void setup();
void check();
void yellowPlay(int a);
void redPlay(int a);
void playToken(int col);
bool checkBoard();
void* handleConnection(void* arg);

vector<vector<int>> Board = {{0}, {0}, {0}, {0}, {0}, {0}, {0}};

enum Colors {
	NO_TOKEN,
	YELLOW_TOKEN,
	RED_TOKEN
};

Texture BoardTexture;
Texture redTokenTexture;
Texture yellowTokenTexture;

Sprite boardSprite;
Sprite redTokens[21];
Sprite yellowTokens[21];

int main(int argc, char* argv[])
{
	char message[1000];
    char buffer[1024];
    int clientSocket;
    struct sockaddr_in serverAddr;
    socklen_t addr_size;

    clientSocket = socket(PF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;

	if(argc >= 3) {
		int port = atoi(argv[2]);
		serverAddr.sin_port = htons(port);
	} else {
		serverAddr.sin_port = htons(1100);
	}

	if(argc >= 2) {
		serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
	} else {
		serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	}
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    addr_size = sizeof serverAddr;
    connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

	pthread_t connection_thread;
	if(pthread_create(&connection_thread, NULL, &handleConnection, &clientSocket)) {
		printf("[ERROR] Failed to create thread\n");
	}
	pthread_join(connection_thread, NULL);

	RenderWindow window(sf::VideoMode(700, 600), "Connect 4");
	setup();

	turn = firstTurn;

	while (window.isOpen())	{
		Vector2i pos;
		Event event;

		while (window.pollEvent(event))		{
			if (event.type == sf::Event::Closed) window.close();

			if(turn == *((int*) myTurn)) {
				if (event.type == Event::KeyPressed){
					if (event.key.code == Keyboard::Num1) {
						if(Board[0].size() < 7) {
							playToken(0);
							turn ^= 1;
							*((int*) msg) = 0;
							send(clientSocket, msg, sizeof(uint32_t), MSG_DONTWAIT);
						} else {
							printf("Illegal move\n");
						}
					}
					if (event.key.code == Keyboard::Num2) {
						if(Board[1].size() < 7) {
							playToken(1);
							turn ^= 1;
							*((int*) msg) = 1;
							send(clientSocket, msg, sizeof(uint32_t), MSG_DONTWAIT);
						} else {
							printf("Illegal move\n");
						}
					}
					if (event.key.code == Keyboard::Num3) {
						if(Board[2].size() < 7) {
							playToken(2);
							turn ^= 1;
							*((int*) msg) = 2;
							send(clientSocket, msg, sizeof(uint32_t), MSG_DONTWAIT);
						} else {
							printf("Illegal move\n");
						}
					}
					if (event.key.code == Keyboard::Num4) {
						if(Board[3].size() < 7) {
							playToken(3);
							turn ^= 1;
							*((int*) msg) = 3;
							send(clientSocket, msg, sizeof(uint32_t), MSG_DONTWAIT);
						} else {
							printf("Illegal move\n");
						}
					}
					if (event.key.code == Keyboard::Num5) {
						if(Board[4].size() < 7) {
							playToken(4);
							turn ^= 1;
							*((int*) msg) = 4;
							send(clientSocket, msg, sizeof(uint32_t), MSG_DONTWAIT);
						} else {
							printf("Illegal move\n");
						}
					}
					if (event.key.code == Keyboard::Num6) {
						if(Board[5].size() < 7) {
							playToken(5);
							turn ^= 1;
							*((int*) msg) = 5;
							send(clientSocket, msg, sizeof(uint32_t), MSG_DONTWAIT);
						} else {
							printf("Illegal move\n");
						}
					}
					if (event.key.code == Keyboard::Num7) {
						if(Board[6].size() < 7) {
							playToken(6);
							turn ^= 1;
							*((int*) msg) = 6;
							send(clientSocket, msg, sizeof(uint32_t), MSG_DONTWAIT);
						} else {
							printf("Illegal move\n");
						}
					}
				}
				window.clear();
				window.draw(boardSprite);
				for (int i = 0;i < 21;i++) {
					window.draw(redTokens[i]);
					window.draw(yellowTokens[i]);
				}
				window.display();
				if (!checkBoard()) {
					sleep(5);
					window.close();
					close(clientSocket);
					exit(0);
				}
			}
			else {
				bzero(msg, sizeof(uint32_t));
				if(recv(clientSocket, msg, sizeof(uint32_t), 0) < 0) {
					printf("[ERROR] Receive of opponent's column play failed\n");
				}
				col = *((int*) msg);
				if(col==7) {
					printf("Opponent disconnected\n");
					window.close();
					close(clientSocket);
					exit(0);
				}
				cout<<"[LOG] Opponent played: "<<col<<endl;
				playToken(col);
				turn ^= 1;
			}
		}
	}
	return 0;
}

void setup(){
	BoardTexture.loadFromFile("images/board.png");
	redTokenTexture.loadFromFile("images/red.png");
	yellowTokenTexture.loadFromFile("images/yellow.png");
	boardSprite.setTexture(BoardTexture);
	for (int i = 0;i < 21;i++)	{
		redTokens[i].setTexture(redTokenTexture);
		redTokens[i].setPosition(800, 700);
		yellowTokens[i].setTexture(yellowTokenTexture);
		yellowTokens[i].setPosition(800, 700);
	}
	firstTime = true;
	counter = 0;
}

bool checkBoard() {

	for (int i = 0;i < WIDTH;i++)	{
		for (int j = 0;j < HEIGHT - 3;j++)		{
			if (Board[i][j] == 1 && Board[i][j + 1] == 1 && Board[i][j + 2] == 1 && Board[i][j + 3] == 1) {
				cout << "Yellow won!\n";
				return false;
			}
			else if (Board[i][j] == 2 && Board[i][j + 1] == 2 && Board[i][j + 2] == 2 && Board[i][j + 3] == 2) {
				cout << "Red won!\n";
				return false;
			}
		}
	}

	for (int i = 0;i < WIDTH - 3;i++)	{
		for (int j = 0;j < HEIGHT;j++)		{
			if (Board[i][j] == 1 && Board[i + 1][j] == 1 && Board[i + 2][j] == 1 && Board[i + 3][j] == 1) {
				cout << "Yellow won!\n";
				return false;
			}
			else if (Board[i][j] == 2 && Board[i + 1][j] == 2 && Board[i + 2][j] == 2 && Board[i + 3][j] == 2) {
				cout << "Red won!\n";
				return false;
			}
		}
	}

	for (int i = 0;i < WIDTH - 3;i++)	{
		for (int j = 0;j < HEIGHT - 3;j++)		{
			if (Board[i][j] == 1 && Board[i + 1][j + 1] == 1 && Board[i + 2][j + 2] == 1 && Board[i + 3][j + 3] == 1) {
				cout << "Yellow won!\n";
				return false;
			}
			else if (Board[i][j] == 2 && Board[i + 1][j + 1] == 2 && Board[i + 2][j + 2] == 2 && Board[i + 3][j + 3] == 2) {
				cout << "Red won!\n";
				return false;
			}
		}
	}

	for (int i = 0;i < WIDTH - 3;i++)	{
		for (int j = HEIGHT - 1;j >= 3;j--)		{
			if (Board[i][j] == 1 && Board[i + 1][j - 1] == 1 && Board[i + 2][j - 2] == 1 && Board[i + 3][j - 3] == 1) {
				cout << "Yellow won!\n";
				return false;
			}
			else if (Board[i][j] == 2 && Board[i + 1][j - 1] == 2 && Board[i + 2][j - 2] == 2 && Board[i + 3][j - 3] == 2) {
				cout << "Red won!\n";
				return false;
			}
		}
	}

	if(Board[0].size() == 7 &&
	   Board[1].size() == 7 && 
	   Board[2].size() == 7 && 
	   Board[3].size() == 7 && 
	   Board[4].size() == 7 && 
	   Board[5].size() == 7) { 
		cout << "Draw\n";
		return false;
	}

	return true;
}

void playToken(int col) {

	if(Board[col].size() < 7 && turn == 0) {
		Board[col].push_back(YELLOW_TOKEN);
		if (j != 21)			{
			yellowTokens[j].setPosition(col * 100, 700 - Board[col].size() * 100);
		}
		j++;
	}

	if(Board[col].size() < 7 && turn == 1) {
		Board[col].push_back(RED_TOKEN);
		if (k != 21)			{
			redTokens[k].setPosition(col * 100, 700 - Board[col].size() * 100);
		}
		k++;
	}
}

void* handleConnection(void* arg) {
	int clientSocket = *((int*) arg);

	if(recv(clientSocket, myTurn, sizeof(uint32_t), 0) < 0) {
		printf("[ERROR] Receive failed\n");
	}
	cout<<"[LOG] My turn: "<<*((int*)myTurn)<<endl;

	pthread_exit(NULL);
}