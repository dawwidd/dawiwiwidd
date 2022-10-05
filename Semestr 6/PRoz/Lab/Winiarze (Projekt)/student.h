#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <vector>
#include <mpi.h>
#include "main.h"

extern int studentId;
extern int chosenWinemakerId;
extern std::vector<int>::iterator it;
extern std::vector<int> studentQueueEntry;

void studentMainLoop();

void partyAndPlanAnotherParty();

void sendRequestsToStudents(bool &requestsSent);

void dealWithWinemaker();

int chooseWinemaker();

int getStudentPositionInQueue(int studentId);

int sendWineAmountToWinemaker(int winemakerId);

void sendWineAmountUpdateToStudents(int winemakerId, int wineAmount);

void resetStudentAcknowledges(std::vector<int> &studentAcknowledges);

void sendAcknowledgeToTheNextPendingStudent();

void sendAcknowledgeToAllPendingStudents();

void *startStudentCommThread(void *ptr);

void handleStudentRequest();

void sendStudentAcknowledge();

void appendStudentRequest();

void handleWinemakerQueue();

void updateDecisionStructure(int studentId, int winemakerId);

void handleWineInfo();

void sendWinemakerOfferQueueToStudents();

void handleStudentAcknowledge();

int countStudentAcknowledges(std::vector<int> &studentAcknowledges);

void handleWineUpdate();
