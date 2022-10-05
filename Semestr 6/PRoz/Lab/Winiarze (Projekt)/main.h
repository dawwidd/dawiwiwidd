#pragma once

#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <iostream>
#include <vector>
#include <mutex>
#include <mpi.h>

// Liczby wątków i zasobów
#define WINEMAKER_COUNT 4
#define STUDENT_COUNT 6
#define SAFEPLACE_COUNT 2

// Datatype wiadomości
typedef struct {
    int lc;     // Zegar Lamporta
    int src;    // Od kogo jest wiadomość
    int data;   // Przesyłane dane
    int wine;
} packet;

extern MPI_Datatype MPI_PACKET;

// processRank i processSize wątku
extern int processSize, processRank;

// Wino
extern int wine;
extern int maxWine;

extern int studentWineRequest;
extern int originalStudentWineRequest;

// Zegar lamporta
extern int lamportClock;
extern std::mutex lamportClockMutex;
extern int latestRequestLamportClock;
extern int latestSafeplaceEntryLamportClock;

// Liczniki ACK i REQ

extern std::vector<int> pendingWinemakers;
extern std::vector<int> winemakersAcknowledges;

extern std::vector<int> pendingStudents;
extern std::vector<int> studentAcknowledges;

// Zmienne pomocnicze
extern int winemakerStatus;
extern int studentStatus;

extern MPI_Status status;
extern packet packetReceive;
extern packet *packetSend;
extern bool isReceivedLamportClockSmaller;
extern bool isReceivedLamportClockEqual;

// Kolejki
extern std::vector<int> studentWinemakersQueue;
extern std::vector<std::vector<int>> studentDecisionStructure;
extern std::vector<std::vector<int>> studentSafePlaceQueue;

// Typy wiadomości
#define REQ 1
#define ACK 2
#define WINE_INFO 3
#define WINEMAKER_QUEUE 4
#define WINE_REQUEST 5
#define WINE_AMOUNT 6
#define WINE_UPDATE 7

// Statusy Winiarzy
#define WAITING_FOR_SAFEPLACE 0
#define IN_SAFE_PLACE 1

// Statusy Studentów
#define WAITING_FOR_TRANSACTION 0
#define IN_TRANSACTION 1
#define PARTYING 2

// Ilość czasu w safeplace
#define SEC_IN_STATE 2

void initParameters(int argc, char **argv);
void initMpi(int *argc, char ***argv);
void run();
int isWinemaker();
void check_thread_support(int provided);
int max(int x, int y);
int min(int x, int y);
void sendPacket(packet *pkt, int destination, int tag);
void finalize();


void debug(std::string message);
std::string getVectorString(std::string title, std::vector<int> &vector);

void incrementLamportClock();
