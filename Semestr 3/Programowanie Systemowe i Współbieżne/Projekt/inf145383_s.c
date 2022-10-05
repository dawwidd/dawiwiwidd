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
#include "inf145383_pub_sub.h"


struct Message msg_s, msg_r; // struktury wiadomosci wychodzących i przychodzących
struct Client Clients[17]; // tablica zalogowanych klientów
struct Subscription Subscriptions[64]; // tablica subskrypcji
struct Blockade Blocks[64]; // tablica blokad użytkowników

int Bans[64]; // Lista użytkowników zbanowanych
int messageCount = 0; // globalna zmienna służąca identyfikacji wiadomości

// Nawiązanie połączenia z serwerem
void connect(int QID)
{
	printf("Nawiazano polaczenie z %d\n", msg_r.sender);				

	msg_r.receiver = msg_s.type+7;
	msg_s.type = OPERATION_SUCCESS;
	msgsnd(QID, &msg_s, sizeof(msg_s), 0);
}

// Logowanie
void login(int QID)
{
	int server_full = 1;
	int ban = 0;

	for(int i=0; i<64; i+=2)
	{
		if(Bans[i] == 0 || Bans[i] == msg_r.sender)
		{
			Bans[i] = msg_r.sender;
			Bans[i+1] += 1;
			break;
		}
	}

	for(int i=0; i<64; i+=2)
	{
		if(Bans[i] == msg_r.sender && Bans[i+1] > 3)
		{
			ban = 1;
			break;
		}
	}
	if(ban == 0)
	{
		for(int i = 1; i < 17; i++) // Sprawdzenie czy jest wolne miejsce
		{
			if(strcmp(Clients[i].name, "")==0)
			{
				server_full = 0;
				break;
			}
		}

		if(server_full) // Serwer pełen
		{
			printf("Nieudana proba logowania uzytkownika %d. Serwer osiagnal maksymalna liczbe uzytkownikow.\n", msg_r.sender);

			msg_s.receiver = msg_r.sender+7;
			msg_s.type = SERVER_OVERFLOW;
			msgsnd(QID, &msg_s, sizeof(msg_s), 0);
		}
		else // Serwer niepełny
		{
			if(strlen(msg_r.shortText) <=3 || strlen(msg_r.shortText) >=15) // Sprawdzenie poprawnosci nazwy uzytkownika
			{
				printf("Nieudana proba logowania uzytkownika %d. Zly login.\n", msg_r.sender);

				msg_s.receiver = msg_r.sender+7;
				msg_s.type = INVALID_USERNAME;
				msgsnd(QID, &msg_s, sizeof(msg_s), 0);
			}
			else // Nazwa poprawna
			{
				int available = 1;
				for(int i = 1; i < 17; i++)
				{
					if(strcmp(Clients[i].name, msg_r.shortText)==0) // Sprawdzenie dostepnosci nazwy
					{
						available = 0;

						printf("Nieudana proba logowania uzytkownika %d. Uzytkownik o podanej nazwie jest juz zalogowany.\n", msg_r.sender);

						msg_s.receiver = msg_r.sender+7;
						msg_s.type = UNAVAILABLE;
						msgsnd(QID, &msg_s, sizeof(msg_s), 0);
						break;
					}
				}
				if(available) // Nick dostepny, dodanie do listy zalogowanych klientów
				{
					for(int i = 1; i < 17; i++)
					{
						if(Clients[i].id == 0)
						{
							Clients[i].id = msg_r.sender;
							strcpy(Clients[i].name, msg_r.shortText);

							printf("Uzytkownik %d zalogowany jako %s.\n", msg_r.sender, msg_r.shortText);

							msg_s.receiver = msg_r.sender+7;
							msg_s.type = OPERATION_SUCCESS;
							msgsnd(QID, &msg_s, sizeof(msg_s), 0);
							break;
						}
					}
				}	
			}
		}
	}
	else
	{
		msg_s.receiver = msg_r.sender+7;
		msg_s.type = BANNED;
		msgsnd(QID, &msg_s, sizeof(msg_s), 0);
	}
	
	
}

// Wylogowanie
void logout(int QID)
{
	int logged = 0;
	
	for(int i = 1; i<17; i++) // Sprawdzenie czy klient wysyłający żądanie jest zalogowany
	{
		if(msg_r.sender == Clients[i].id) logged = 1;
	}

	if(logged) // Usunięcie użytkownika z listy zalogowanych klientów
	{
		printf("Uzytkownik %d wylogowal sie.\n", msg_r.sender);

		for(int i = 1; i<17; i++)
		{
			if(Clients[i].id == msg_r.sender)
			{
				Clients[i].id = 0;
				strcpy(Clients[i].name, "");
				break;
			}
		}

		for(int i=0; i<64; i++) // Wyczyszczenie informacji o subskrybcjach wylogowanego uzytkownika
		{
			if(Subscriptions[i].id == msg_r.sender)
			{
				Subscriptions[i].id = 0;
				Subscriptions[i].channel = 0;
			}
		}

		msg_s.receiver = msg_r.sender+7;
		msg_s.type = OPERATION_SUCCESS;
		msgsnd(QID, &msg_s, sizeof(msg_s), 0);
	}
	else // Użytkownik nie był zalogowany
	{
		printf("Uzytkownik %d nie jest zalogowany.\n", msg_r.sender);

		msg_s.receiver = msg_r.sender+7;
		msg_s.type = SENDER_NOT_RECOGNIZED;
		msgsnd(QID, &msg_s, sizeof(msg_s), 0);
	}
}

// Zasubskrybowanie kanału
void subscribe(int QID, int Channels[])
{
	int logged = 0;
	
	for(int i = 1; i<17; i++) // Sprawdzenie czy klient wysyłający żądanie jest zalogowany
	{
		if(msg_r.sender == Clients[i].id)
		{
			logged = 1;
			break;
		}
	}

	if(logged == 1)
	{
		int available = 1;
		int ch_exists = 0;

		for(int i=0; i<16; i++)
		{
			if(Channels[i] == atoi(msg_r.shortText)) // Sprawdzenie czy podany kanał jest dostępny na liście
			{
				ch_exists = 1;
				break;
			}
		}
		if(ch_exists == 1)
		{
			for(int i = 0; i < 64; i++) // Sprawdzenie czy użytkownik nie subskrybuje już podanego kanału
			{
				if(msg_r.sender == Subscriptions[i].id && atoi(msg_r.shortText) == Subscriptions[i].channel)
				{
					available = 0;

					printf("Nieudana proba zasubskrybowania kanalu %d przez uzytkownika %d. Ten uzytkownik subskrybuje juz podany kanal.\n", atoi(msg_r.shortText), msg_r.sender);

					msg_s.receiver = msg_r.sender+7;
					msg_s.type = UNAVAILABLE;
					msgsnd(QID, &msg_s, sizeof(msg_s), 0);
					break;
				}
			}
			if(available) // Dodanie nowej subskrybcji do listy
			{
				for(int i=0; i<64; i++)
				{
					if(Subscriptions[i].id == 0)
					{
						Subscriptions[i].id = msg_r.sender;
						Subscriptions[i].channel = atoi(msg_r.shortText);
						Subscriptions[i].quantity = atoi(msg_r.longText);

						if(Subscriptions[i].quantity == 0) printf("Uzytkownik %d trwale zasubskrybowal kanal %d.\n", Subscriptions[i].id, Subscriptions[i].channel);
						else printf("Uzytkownik %d zasubskrybowal kanal %d na %d wiadomosci.\n", Subscriptions[i].id, Subscriptions[i].channel, Subscriptions[i].quantity);
						msg_s.receiver = msg_r.sender+7;
						msg_s.type = OPERATION_SUCCESS;
						msgsnd(QID, &msg_s, sizeof(msg_s), 0);
						break;
					}
				}
			}
		}
		else // Podany kanał nie istnieje
		{
			msg_s.receiver = msg_r.sender+7;
			msg_s.type = NO_CHANNEL;
			msgsnd(QID, &msg_s, sizeof(msg_s), 0);
		}
	}
	else // Użytkownik nie jest zalogowany
	{
		printf("Uzytkownik %d nie jest zalogowany.\n", msg_r.sender);

		msg_s.receiver = msg_r.sender+7;
		msg_s.type = SENDER_NOT_RECOGNIZED;
		msgsnd(QID, &msg_s, sizeof(msg_s), 0);
	}
}

// Odsubskrybowanie kanału
void unsubscribe(int QID, int Channels[])
{
	int logged = 0;
	int success = 0;
	
	for(int i = 1; i<17; i++) // Sprawdzenie czy klient jest zalogowany
	{
		if(msg_r.sender == Clients[i].id) logged = 1;
	}

	if(logged == 1)
	{
		int ch_exists = 0;

		for(int i=0; i<16; i++) // Sprawdzenie czy podany kanał istnieje
		{
			if(Channels[i] == atoi(msg_r.shortText))
			{
				ch_exists = 1;
				break;
			}
		}

		if(ch_exists == 1) // Usunięcie informacji o subskrypcji z listy
		{
			for(int i=0; i<64; i++)
			{
				if(Subscriptions[i].id == msg_r.sender && Subscriptions[i].channel == atoi(msg_r.shortText))
				{
					Subscriptions[i].id = 0;
					Subscriptions[i].channel = 0;

					msg_s.receiver = msg_r.sender+7;
					msg_s.type = OPERATION_SUCCESS;
					msgsnd(QID, &msg_s, sizeof(msg_s), 0);
					success = 1;
					break;
				}
			}
			if(success == 0) // Użytkownik nie subskrybował podanego kanału
			{
				msg_s.receiver = msg_r.sender+7;
				msg_s.type = UNAVAILABLE;
				msgsnd(QID, &msg_s, sizeof(msg_s), 0);
			}
			
		}
		else // Podany kanał nie istnieje
		{
			msg_s.receiver = msg_r.sender+7;
			msg_s.type = NO_CHANNEL;
			msgsnd(QID, &msg_s, sizeof(msg_s), 0);
		}
		
	}
	else // Użytkownik nie jest zalogowany
	{
		printf("Uzytkownik %d nie jest zalogowany.\n", msg_r.sender);

		msg_s.receiver = msg_r.sender+7;
		msg_s.type = SENDER_NOT_RECOGNIZED;
		msgsnd(QID, &msg_s, sizeof(msg_s), 0);
	}
	
	
}

// Rejestracja nowego kanału komunikacyjnego
void msgreg(int QID, int Channels[])
{
	int logged = 0;
	
	for(int i = 1; i<17; i++) // Sprawdzenie czy klient jest zalogowany
	{
		if(msg_r.sender == Clients[i].id)
		{
			logged = 1;
			break;
		}
	}

	if(logged == 1)
	{
		int available = 1;
		for(int i = 0; i < 16; i++) // Sprawdzenie czy kanał już istnieje
		{
			if(Channels[i] == atoi(msg_r.shortText))
			{
				available = 0;

				printf("Nieudana proba zarejestrowania kanalu %d przez uzytkownika %d. Kanal juz istnieje.\n", atoi(msg_r.shortText), msg_r.sender);

				msg_s.receiver = msg_r.sender+7;
				msg_s.type = UNAVAILABLE;
				msgsnd(QID, &msg_s, sizeof(msg_s), 0);
				break;
			}
		}
		if(available)
		{
			for(int i=0; i<16; i++) // Dodanie nowego kanału do listy
			{
				if(Channels[i] == 0)
				{
					Channels[i] = atoi(msg_r.shortText);
					
					printf("Uzytkownik %d zarejestrowal kanal %d.\n", msg_r.sender, Channels[i]);
					
					msg_s.receiver = msg_r.sender+7;
					msg_s.type = OPERATION_SUCCESS;
					msgsnd(QID, &msg_s, sizeof(msg_s), 0);
					break;
				}
			}
			for(int i=1; i<17; i++) // Rozgłoszenie wiadomości o nowym kanale do wszystkich zalogowanych użytkowników
			{
				if(Clients[i].id != 0)
				{
					msg_s.receiver = Clients[i].id+8;
					msg_s.type = NEW_CHANNEL;
					strcpy(msg_s.shortText, msg_r.shortText);
					msgsnd(QID, &msg_s, sizeof(msg_s), 0);
				}
			}
		}
	}
	else // Użytkownik nie jest zalogowany
	{
		printf("Uzytkownik %d nie jest zalogowany.\n", msg_r.sender);

		msg_s.receiver = msg_r.sender+7;
		msg_s.type = SENDER_NOT_RECOGNIZED;
		msgsnd(QID, &msg_s, sizeof(msg_s), 0);
	}
}

// Nadanie wiadomosci użytkownika przez podany kanał
void broadcast(int QID, int Channels[])
{
	int logged = 0;
	
	for(int i = 1; i<17; i++) // Sprawdzenie czy użytkownik jest zalogowany
	{
		if(msg_r.sender == Clients[i].id)
		{
			logged = 1;
			break;
		}
	}

	if(logged == 1)
	{
		int ch_exists = 0;

		for(int i=0; i<16; i++) // Sprawdzenie czy podany kanał istnieje
		{
			if(Channels[i] == atoi(msg_r.shortText))
			{
				ch_exists = 1;
				break;
			}
		}

		if(ch_exists == 1)
		{
			printf("Uzytkownik %d nadal wiadomosc na kanale %d.\n", msg_r.sender, atoi(msg_r.shortText));

			msg_s.receiver = msg_r.sender+7;
			msg_s.type = OPERATION_SUCCESS;
			msgsnd(QID, &msg_s, sizeof(msg_s), 0);
			int banned;

			for(int i=0; i<64; i++) // Nadanie wiadomosci do wszystkich użytkowników, którzy subskrybują podany kanał
			{
				if(Subscriptions[i].channel == atoi(msg_r.shortText))
				{
					banned = 0;
					for(int j=0; j<16; j++) // Wykluczenie nadawania do użytkowników, którzy zbanowali nadawcę
					{
						if(msg_r.sender == Blocks[j].blocked && Subscriptions[i].id == Blocks[j].blocker)
						{
							banned = 1;
							break;
						}
					}
					if(banned == 0)
					{
						messageCount++;
						Subscriptions[i].quantity--; // Zmniejszenie trwałości subskrypcji. Dla subskrypcji trwałej (0), poniższy warunek nigdy się nie wykona.

						msg_s.receiver = Subscriptions[i].id;

						if(Subscriptions[i].quantity == 0)
						{
							Subscriptions[i].id = 0;
							Subscriptions[i].channel = 0;
						}
						
						msg_s.type = messageCount;
						strcpy(msg_s.longText, msg_r.longText);
						msg_s.type = Subscriptions[i].quantity;
						msgsnd(QID, &msg_s, sizeof(msg_s), 0);
					}
				}
			}
		}
		else // Podany kanał nie istnieje
		{
			msg_s.receiver = msg_r.sender+7;
			msg_s.type = NO_CHANNEL;
			msgsnd(QID, &msg_s, sizeof(msg_s), 0);
		}
	}
	else // Użytkownik nie jest zalogowany
	{
		printf("Uzytkownik %d nie jest zalogowany.\n", msg_r.sender);

		msg_s.receiver = msg_r.sender+7;
		msg_s.type = SENDER_NOT_RECOGNIZED;
		msgsnd(QID, &msg_s, sizeof(msg_s), 0);
	}
}

// Blokowanie wiadomości od użytkownika
void block(int QID)
{
	int logged = 0;
	int bannedId = 0;
	
	for(int i = 1; i<17; i++) // Sprawdzenie czy klient jest zalogowany
	{
		if(msg_r.sender == Clients[i].id)
		{
			logged = 1;
			break;
		}
	}

	if(logged == 1)
	{
		int status = 0;
		for(int i = 1; i < 17; i++)
		{
			if(strcmp(Clients[i].name, msg_r.shortText)==0) // Wyszukanie id targetowanego użytkownika po nazwie
			{
				status = 1;
				bannedId = Clients[i].id;
				break;
			}
		}

		for(int i=0; i<64; i++) // Sprawdzenie czy użytkownik nie blokuje już podanego klienta
		{
			if(msg_r.sender == Blocks[i].blocker && bannedId == Blocks[i].blocked)
			{
				status = 2;
				break;
			}
		}
		if(status == 1) // Dodanie użytkowników do listy blokad
		{
			for(int i=0; i<64; i++)
			{
				if(Blocks[i].blocker == 0)
				{
					Blocks[i].blocker = msg_r.sender;
					Blocks[i].blocked = bannedId;

					printf("Uzytkownik %d zablokowal wiadomosci od uzytkownika %d.\n", Blocks[i].blocker, Blocks[i].blocked);
					
					msg_s.receiver = msg_r.sender+7;
					msg_s.type = OPERATION_SUCCESS;
					msgsnd(QID, &msg_s, sizeof(msg_s), 0);
					break;
				}
			}
		}
		else if(status == 0) // Targetowany użytkownik nie jest zalogowany
		{
			printf("Nieudana proba zablokowania uzytkownika %s przez uzytkownika %d. Uzytkownik o podanej nazwie nie jest zalogowany.\n", msg_r.shortText, msg_r.sender);

			msg_s.receiver = msg_r.sender+7;
			msg_s.type = INVALID_USERNAME;
			msgsnd(QID, &msg_s, sizeof(msg_s),0);
		}
		else // Targetowany użytkownik jest już zablokowany przez klienta
		{
			printf("Nieudana proba ponownego zablokowania uzytkownika %s przez uzytkownika %d.\n", msg_r.shortText, msg_r.sender);

			msg_s.receiver = msg_r.sender+7;
			msg_s.type = UNAVAILABLE;
			msgsnd(QID, &msg_s, sizeof(msg_s), 0);
		}
	}
	else // Użytkownik nie jest zalogowany
	{
		printf("Uzytkownik %d nie jest zalogowany.\n", msg_r.sender);

		msg_s.receiver = msg_r.sender+7;
		msg_s.type = SENDER_NOT_RECOGNIZED;
		msgsnd(QID, &msg_s, sizeof(msg_s), 0);
	}
}

// Odblokowanie wiadomosci od użytkownika
void unblock(int QID)
{
	int logged = 0;
	int bannedId = 0;
	
	for(int i = 1; i<17; i++) // Sprawdzenie czy klient jest zalogowany
	{
		if(msg_r.sender == Clients[i].id)
		{
			logged = 1;
			break;
		}
	}

	if(logged == 1)
	{
		int status = 0;
		for(int i = 1; i < 17; i++)
		{
			if(strcmp(Clients[i].name, msg_r.shortText)==0) // Wyszukanie id targetowanego klienta po nazwie
			{
				status = 1;
				bannedId = Clients[i].id;
				break;
			}
		}
		if(status == 1) // Targetowany użytkownik jest zalogowany
		{
			for(int i = 0; i < 64; i++)
			{
				if(msg_r.sender == Blocks[i].blocker && bannedId == Blocks[i].blocked) // Wyszukanie i wyzerowanie informacji o blokadzie
				{
					status = 2;
					Blocks[i].blocker = 0;
					Blocks[i].blocked = 0;
					break;
				} 
			}
			if(status == 2) // Odblokowanie targetowanego klienta
			{
				msg_s.receiver = msg_r.sender+7;
				msg_s.type = OPERATION_SUCCESS;
				msgsnd(QID, &msg_s, sizeof(msg_s), 0);
			}
			else // Targetowany klient nie był zablokowany
			{
				msg_s.receiver = msg_r.sender+7;
				msg_s.type = UNAVAILABLE;
				msgsnd(QID, &msg_s, sizeof(msg_s), 0);
			}
		}
		else // Targetowany klient nie był zalogowany
		{
			msg_s.receiver = msg_r.sender+7;
			msg_s.type = INVALID_USERNAME;
			msgsnd(QID, &msg_s, sizeof(msg_s), 0);
		}
		
	}
	else // Użytkownik nie jest zalogowany
	{
		printf("Uzytkownik %d nie jest zalogowany.\n", msg_r.sender);

		msg_s.receiver = msg_r.sender+7;
		msg_s.type = SENDER_NOT_RECOGNIZED;
		msgsnd(QID, &msg_s, sizeof(msg_s), 0);
	}
}

// [Debug] Wyświetlenie listy zalogowanych użytkowników
void users(int QID)
{
	for(int i=1; i<17; i++)
	{
		printf("%d. %d %s\n", i, Clients[i].id, Clients[i].name);
	}
}

// [Debug] Wyświetlenie listy z informacjami o subskrypcjach
void subslist(int QID)
{
	for(int i=0; i<17; i++)
	{
		printf("%d. %d %d %d\n", i, Subscriptions[i].id, Subscriptions[i].channel, Subscriptions[i].quantity);
	}
}

// [Debug] Wyświetlenie listy dostępnych kanałów
void channellist(int QID, int Channels[])
{
	for(int i=0; i<16; i++)
	{
		printf("%d. %d\n", i, Channels[i]);
	}
}

// [Debug] Wyświetlenie listy z informacjami o blokadach między użytkownikami
void blocks(int QID)
{
	for(int i=0; i<16; i++)
	{
		printf("%d. %d %d\n", i, Blocks[i].blocker, Blocks[i].blocked);
	}
}

int main(int argc, char *argv[])
{
	int QID = msgget(0x420, 0600 | IPC_CREAT);
	int Channels[16];
	for(int i=0; i<16; i++) Channels[i] = 0;
	int logcount = 0;


	do // Główna pętla
	{
		msgrcv(QID, &msg_r, sizeof(msg_r), 1, 0);

		switch(msg_r.type)
		{
			case CONNECTION: connect(QID); logcount++; break;
			case LOGIN: login(QID); break;
			case LOGOUT: logout(QID); break;
			case SUBSCRIBE: subscribe(QID, Channels); break;
			case UNSUBSCRIBE: unsubscribe(QID, Channels); break;
			case MSGREG: msgreg(QID, Channels); break;
			case MESSAGE: broadcast(QID, Channels); break;
			case BLOCK: block(QID); break;
			case UNBLOCK: unblock(QID); break;
			case QUIT: logcount--; break;
			case USERS: users(QID); break; // [Debug]
			case SUBSLIST: subslist(QID); break; // [Debug]
			case CHANNELLIST: channellist(QID, Channels); break; // [Debug]
			case BANS: blocks(QID); break; // [Debug]
		}
	} while(logcount > 0); // Wyłącz serwer jeśli wszyscy wcześniej połączeni użytkownicy zamknęli klienty

	return 0;
}