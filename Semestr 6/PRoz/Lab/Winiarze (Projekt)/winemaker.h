#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <vector>
#include <mutex>
#include <mpi.h>
#include "main.h"

void winemakerMainLoop();

void produceWine();

void sendSafeplaceRequests(bool &requestsSent);

void sendAcknowledgeToTheNextPendingWinemaker();

// Z kartki, działa gorzej niż rozwiązanie wyżej
void sendAcknowledgeToAllPendingWinemakers();

void *startWinemakerCommThread(void *ptr);

void handleSafeplaceRequest();

void handleWinemakerAcknowledge();

void handleWineRequest();

void sendWineInfoToStudents();

int countAcknowledges(std::vector<int> &winemakersAcknowledges);

void resetAcknowledges(std::vector<int> &winemakersAcknowledges);

void sendSafeplaceRequest();

void sendWinemakerAcknowledge();

void sendWineAmount();
