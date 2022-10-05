#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/mman.h>
#include "inf145383_pub_sub.h"


struct Message msg_s, msg_r; // Struktury wiadomości wychodzących i przychodzących

// Nawiązanie połączenia z serwerem
int connect(int QID)
{
	msg_s.receiver = 1;
	msg_s.type = CONNECTION;
	msg_s.sender = getpid();
	msgsnd(QID, &msg_s, sizeof(msg_s), 0);
	
	if(msgrcv(QID, &msg_r, sizeof(msg_r), getpid()+7, IPC_NOWAIT) == -1)
	{
		printf("Połączono z serwerem.\n");
		return 1;
	}
	return 0;
}

// Logowanie 
int login(int QID, char nick[])
{
	msg_s.receiver = 1;
	msg_s.type = LOGIN;
	msg_s.sender = getpid();
	strcpy(msg_s.shortText, nick);
	msgsnd(QID, &msg_s, sizeof(msg_s),0);


	msgrcv(QID, &msg_r, sizeof(msg_r), getpid()+7, 0);
	if(msg_r.type == OPERATION_SUCCESS){ printf("Zalogowano pomyslnie.\n"); return 1;}
	else if(msg_r.type == INVALID_USERNAME){ printf("Zly nick. Sprobuj ponownie.\n"); return 0;}
	else if(msg_r.type == UNAVAILABLE){ printf("Klient o podanym nicku jest juz zalogowany.\n"); return 0;}
	else if(msg_r.type == SERVER_OVERFLOW){ printf("Brak miejsca na wiecej klientow.\n"); return 0;}
	else if(msg_r.type == BANNED){ printf("Zostałeś zbanowany za zbyt duza liczbe prob logowania.\n"); return 2;}
	else { printf("Wystapil nieoczekiwany blad.\n"); return 0; }
}

// Wylogowanie
int logout(int QID)
{
	msg_s.receiver = 1;
	msg_s.type = LOGOUT;
	msg_s.sender = getpid();
	msgsnd(QID, &msg_s, sizeof(msg_s), 0);

	msgrcv(QID, &msg_r, sizeof(msg_r), getpid()+7, 0);
	if(msg_r.type == OPERATION_SUCCESS) { printf("Wylogowano pomyslnie.\n"); return 1; }
	else if(msg_r.type == SENDER_NOT_RECOGNIZED) { printf("Musisz byc zalogowany aby moc wykonac ta operacje.\n"); return 0; }
	else { printf("Wystapil nieoczekiwany blad.\n"); return 0; }
}

// Zasubskrybowanie podanego kanału na podaną ilość wiadomości (quantity = 0 - subskrybcja trwała)
int subscribe(int QID, char channel[], char quantity[])
{
	msg_s.receiver = 1;
	msg_s.type = SUBSCRIBE;
	msg_s.sender = getpid();
	strcpy(msg_s.shortText, channel);
	strcpy(msg_s.longText, quantity);
	msgsnd(QID, &msg_s, sizeof(msg_s),0);

	msgrcv(QID, &msg_r, sizeof(msg_r), getpid()+7, 0);
	if(msg_r.type == OPERATION_SUCCESS){ printf("Pomyslnie zasubskrybowano kanal %d.\n", atoi(channel)); return 1; }
	else if(msg_r.type == UNAVAILABLE){ printf("Kanal %d jest juz zasubskrybowany.\n", atoi(channel)); return 0; }
	else if(msg_r.type == SENDER_NOT_RECOGNIZED){ printf("Musisz byc zalogowany aby moc wykonac ta operacje.\n"); return 0; }
	else if(msg_r.type == NO_CHANNEL) { printf("Kanal o podanym numerze (%d) nie istnieje.\n", atoi(channel)); return 0; }
	else { printf("Wystapil nieoczekiwany blad.\n"); return 0; }
}

// Odsubskrybowanie podanego kanału
int unsubscribe(int QID, char channel[])
{
	msg_s.receiver = 1;
	msg_s.type = UNSUBSCRIBE;
	msg_s.sender = getpid();
	strcpy(msg_s.shortText, channel);
	msgsnd(QID, &msg_s, sizeof(msg_s),0);

	msgrcv(QID, &msg_r, sizeof(msg_r), getpid()+7, 0);
	if(msg_r.type == OPERATION_SUCCESS){ printf("Pomyslnie odsubskrybowano kanal %d\n", atoi(channel)); return 1; }
	else if(msg_r.type == SENDER_NOT_RECOGNIZED){ printf("Musisz byc zalogowany aby moc wykonac ta operacje.\n"); return 0; }
	else if(msg_r.type == NO_CHANNEL) { printf("Kanal o podanym numerze (%d) nie istnieje.\n", atoi(channel)); return 0; }
	else if(msg_r.type == UNAVAILABLE) { printf("Kanal o podanym numerze (%d) nie jest zasubskrybowany.\n", atoi(channel)); return 0; }
	else { printf("Wystapil nieoczekiwany blad.\n"); return 0; }
}

// Zarejestrowanie nowego kanału komunikacyjnego
int msgreg(int QID, char channel[])
{
	msg_s.receiver = 1;
	msg_s.type = MSGREG;
	msg_s.sender = getpid();
	strcpy(msg_s.shortText, channel);
	msgsnd(QID, &msg_s, sizeof(msg_s),0);

	msgrcv(QID, &msg_r, sizeof(msg_r), getpid()+7, 0);
	if(msg_r.type == OPERATION_SUCCESS) { printf("Pomyslnie zarejestrowano kanal %d.\n", atoi(channel)); return 1; }
	else if(msg_r.type == SENDER_NOT_RECOGNIZED) { printf("Musisz byc zalogowany aby moc wykonac ta operacje.\n"); return 0; }
	else if(msg_r.type == UNAVAILABLE) { printf("Ten typ wiadomosci jest juz zarejestrowany.\n"); return 0; }
	else { printf("Wystapil nieoczekiwany blad.\n"); return 0; }
}

// Nadanie wiadomości na podanym kanale
int sndmsg(int QID, char channel[], char text[], char username[])
{
	msg_s.receiver = 1;
	msg_s.type = MESSAGE;
	msg_s.sender = getpid();

	//Dodanie do wiadomości informacji kto nadał wiadomość na jakim kanale
	char text2[275] = "";
	strcat(text2, channel);
	strcat(text2, " ");
	strcat(text2, username);
	strcat(text2, ": ");
	strcat(text2, text);

	strcpy(msg_s.shortText, channel);
	strcpy(msg_s.longText, text2);
	msgsnd(QID, &msg_s, sizeof(msg_s), 0);

	msgrcv(QID, &msg_r, sizeof(msg_r), getpid()+7, 0);
	if(msg_r.type == OPERATION_SUCCESS) { printf("Pomyslnie wyslano wiadomosc na kanale %d.\n", atoi(channel)); return 1; }
	else if(msg_r.type == SENDER_NOT_RECOGNIZED) { printf("Musisz byc zalogowany aby moc wykonac ta operacje.\n"); return 0; }
	else if(msg_r.type == NO_CHANNEL) { printf("Kanal o podanym numerze (%d) nie istnieje.\n", atoi(channel)); return 0; }
	else { printf("Wystapil nieoczekiwany blad.\n"); return 0; }	
}

// Odczytanie wszystkich przychodzących wiadomości
int rdmsg(int QID, int pid, int *subcount)
{
	msgrcv(QID, &msg_r, sizeof(msg_r), pid, 0);
	if(msg_r.type == 0) *subcount -= 1; // Zmiejszenie licznika subskrypcji jeśli upłynęła trwałość

	printf("%s\n", msg_r.longText);

	int poprz = msg_r.type;

	while(1) // Odczytywanie wiadomości, dopóki pojawiają się nowe
	{
		msgrcv(QID, &msg_r, sizeof(msg_r), pid, IPC_NOWAIT);
		if(msg_r.type == poprz) return 1;
		if(msg_r.type == 0) *subcount -= 1;

		poprz = msg_r.type;

		printf("%s\n", msg_r.longText);
	}
}

// Blokowanie wiadomości od użytkownika
int block(int QID, char nick[])
{
	msg_s.receiver = 1;
	msg_s.type = BLOCK;
	msg_s.sender = getpid();

	strcpy(msg_s.shortText, nick);
	msgsnd(QID, &msg_s, sizeof(msg_s), 0);

	msgrcv(QID, &msg_r, sizeof(msg_r), getpid()+7, 0);
	if(msg_r.type == OPERATION_SUCCESS) { printf("Pomyslnie zablokowano uzytkownika %s.\n", nick); return 1; }
	else if(msg_r.type == SENDER_NOT_RECOGNIZED) { printf("Musisz byc zalogowany aby moc wykonac ta operacje.\n"); return 0; }
	else if(msg_r.type == INVALID_USERNAME) { printf("Uzytkownik o nazwie %s nie jest zalogowany.\n", nick); return 0; }
	else if(msg_r.type == UNAVAILABLE) { printf("Uzytkownik o nazwie %s jest juz zablokowany.\n", nick); return 0; }
	else { printf("Wystapil nieoczekiwany blad.\n"); return 0; }
}

// Odblokowanie wiadomości od użytkownika
int unblock(int QID, char nick[])
{
	msg_s.receiver = 1;
	msg_s.type = UNBLOCK;
	msg_s.sender = getpid();

	strcpy(msg_s.shortText, nick);
	msgsnd(QID, &msg_s, sizeof(msg_s), 0);

	msgrcv(QID, &msg_r, sizeof(msg_r), getpid()+7, 0);
	if(msg_r.type == OPERATION_SUCCESS) { printf("Pomyslnie odblokowano uzytkownika %s.\n", nick); return 1; }
	else if(msg_r.type == SENDER_NOT_RECOGNIZED) { printf("Musisz byc zalogowany aby moc wykonac ta operacje.\n"); return 0; }
	else if(msg_r.type == INVALID_USERNAME) { printf("Uzytkownik o nazwie %s nie jest zalogowany.\n", nick); return 0; }
	else if(msg_r.type == UNAVAILABLE) { printf("Uzytkownik o nazwie %s nie jest zablokowany.\n", nick); return 0; }
	else { printf("Wystapil nieoczekiwany blad.\n"); return 0; }
}

// Wysłanie do serwera wiadomości o zamknięciu klienta
void quit(int QID)
{
	msg_s.receiver = 1;
	msg_s.type = QUIT;
	msg_s.sender = getpid();

	msgsnd(QID, &msg_s, sizeof(msg_s), 0);
}

// [Debug] Wyświetlenie listy użytkowników
void users(int QID)
{
	msg_s.receiver = 1;
	msg_s.type = USERS;
	msg_s.sender = getpid();
	msgsnd(QID, &msg_s, sizeof(msg_s), 0);
}

// [Debug] Wyświetlenie listy z informacjami o subskrypcjach
void subslist(int QID)
{
	msg_s.receiver = 1;
	msg_s.type = SUBSLIST;
	msg_s.sender = getpid();
	msgsnd(QID, &msg_s, sizeof(msg_s), 0);
}

// [Debug] Wyświetlenie listy dostępnych kanałów komunikacyjnych
void channellist(int QID)
{
	msg_s.receiver = 1;
	msg_s.type = CHANNELLIST;
	msg_s.sender = getpid();
	msgsnd(QID, &msg_s, sizeof(msg_s), 0);
}

// [Debug] Wyświetlenie listy z informacjami o blokadach między użytkownikami
void blocks(int QID)
{
	msg_s.receiver = 1;
	msg_s.type = BANS;
	msg_s.sender = getpid();
	msgsnd(QID, &msg_s, sizeof(msg_s), 0);
}


int main(int argc, char *argv[])
{
	int QID = msgget(0x420, 0600 | IPC_CREAT);
	char action[16]; // Komendy klienta
	char username[64]; // Nazwa klienta
	char username2[64]; // Nazwa adresata
	char channel[8]; // Numer kanału
	char quantity[8]; // Trwałość subskrypcji
	char text[256]; // Treść wiadomości
	int listener = 0; // PID procesu nasłuchującego sygnałów asynchronicznych z serwera (w tym momencie tylko NEW_MESSAGE)
	int asyncpid = 0; // PID procesu nasłuchującego zasubskrybowanych kanałów i odbierającego wiadomości od użytkowników automatycznie
	int logged = 0; // Przełącznik statusu zalogowania użytkownika

	// Zmienne współdzielone między procesem głównym klienta, a nasłuchującymi
	int *subcount = mmap(NULL, sizeof subcount, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0); // liczba aktualnych subskrypcji
	int *async = mmap(NULL, sizeof async, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0); // Przełącznik trybu asynchronicznego
	*subcount = 0;
	*async = 0;
	
	if((listener = fork())==0) // Proces nasłuchujący asynchronicznych sygnałów z serwera
	{
		while(1)
		{
			msgrcv(QID, &msg_r, sizeof(msg_r), getppid()+8, 0);
			if(msg_r.type == NEW_CHANNEL)printf("Powstal nowy kanal (%d).\n", atoi(msg_r.shortText));
		}
	}


	if(connect(QID)) // Sprawdzenie czy połączono z serwerem (niestety tylko prowizoryczne)
	{
		while(1) // Główna pętla
		{
			printf("> ");
			scanf("%s", action);
			
			
			if(strcmp(action, "login")==0) // Logowanie
			{
				if(logged == 0)
				{
					scanf("%s", username);
					logged = login(QID, username);
					if(logged == 2)
					{
						kill(listener, 9);
						if(asyncpid != 0)kill(asyncpid, 9); // Tylko jeśli był uruchomiony
						quit(QID);
						break;
					}
				}
				else printf("Jestes juz zalogowany.\n");		
			}
			else if(strcmp(action, "logout")==0) // Wylogowanie
			{
				if(logout(QID)) logged = 0;
			}
			else if(strcmp(action, "sub")==0) // Subskrybowanie
			{
				scanf("%s %s", channel, quantity);
				if(subscribe(QID, channel, quantity)==1) *subcount += 1;
			}
			else if(strcmp(action, "unsub")==0) // Odsubskrybowanie
			{
				scanf("%s", channel);
				if(unsubscribe(QID, channel)==1) *subcount -= 1;
			}
			else if(strcmp(action, "msgreg")==0) // Rejestrowanie nowego kanału
			{
				scanf("%s", channel);
				msgreg(QID, channel);
			}
			else if(strcmp(action, "sndmsg")==0) // Nadawnie wiadomości
			{
				scanf("%s ", channel);
				fgets(text, 256, stdin);
				text[strcspn(text, "\n")] = 0;
				
				sndmsg(QID, channel, text, username);
			}
			else if(strcmp(action, "rdmsg")==0) // Odczytywanie wiadomości
			{
				if(*subcount > 0) rdmsg(QID, getpid(), subcount); // Tylko jeśli są subskrybcje, inaczej klient by się zawiesił
				else printf("Nie zasubskrybowano zadnego kanalu.\n");
			}
			else if(strcmp(action, "async")==0) // Tryb asynchroniczny
			{
				*async ^= 1;

				if(*async == 1)
				{
					printf("Aktywowano odbior asynchroniczny.\n");
					if((asyncpid = fork()) == 0)
					{
						while(1)
						{
							if(*subcount > 0) rdmsg(QID, getppid(), subcount);
							else
							{
								printf("Nie zasubskrybowano zadnego kanalu.\n");
								break;
							}
						}
						*async ^= 1;
						printf("Dezaktywowano odbior asynchroniczny.\n");
						kill(getpid(), 9);
					}
				}
				else
				{
					printf("Dezaktywowano odbior asynchroniczny.\n");
					kill(asyncpid, 9);
				}
			}
			else if(strcmp(action, "quit")==0) // Wyłączenie klienta, zabicie jego procesów potomnych
			{
				if(logged == 1)logout(QID);
				kill(listener, 9);
				if(asyncpid != 0)kill(asyncpid, 9); // Tylko jeśli był uruchomiony
				quit(QID);
				break;
			}
			// else if(strcmp(action, "subcount")==0) // [Debug] Wyświetlenie licznika subskrypcji
			// {
			// 	printf("%d\n", *subcount);
			// }
			else if(strcmp(action, "block")==0) // Blokowanie użytkownika
			{
				scanf("%s", username2);
				block(QID, username2);
			}
			else if(strcmp(action, "unblock")==0) // Oblokowanie użytkownika
			{
				scanf("%s", username2);
				unblock(QID, username2);
			}
			else if(strcmp(action, "users")==0) // [Debug] Lista zalogowanych użytkowników
			{
				users(QID);
			}
			else if(strcmp(action, "subslist")==0) // [Debug] Lista subskrypcji
			{
				subslist(QID);
			}
			else if(strcmp(action, "chlist")==0) // [Debug] Lista kanałów
			{
				channellist(QID);
			}
			else if(strcmp(action, "blocks")==0) // [Debug] Lista blokad
			{
				blocks(QID);
			}
			strcpy(action, ""); // Wyczyszczenie bufora komend
		}
	}
	munmap(subcount, sizeof *subcount);
	munmap(async, sizeof *async);

	return 0;
}