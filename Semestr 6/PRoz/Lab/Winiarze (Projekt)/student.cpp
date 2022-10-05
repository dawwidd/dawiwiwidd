#include "student.h"

int studentId;
int chosenWinemakerId;
int myPositionInStudentQueue = STUDENT_COUNT;
std::vector<int> studentQueueEntry;
std::vector<int> studentLamportClocks(STUDENT_COUNT);
std::vector<int> wineOfferWinemakerIds;
std::vector<int> wineOfferWineAmounts;
std::mutex pendingStudentsMutex;

void studentMainLoop() {
    bool requestsSent = false;

    wineOfferWineAmounts.resize(WINEMAKER_COUNT);
    std::fill(wineOfferWineAmounts.begin(), wineOfferWineAmounts.end(), 0);

    srand(time(NULL)*processRank);
    while(true) {
        if (!requestsSent) {
            if(studentWineRequest <= 0) {
                partyAndPlanAnotherParty();
            }
            sendRequestsToStudents(requestsSent);
        }

        // Zablokuj wątek do momentu otrzymania zgody na transakcję z winiarzem
        MPI_Recv(&packetReceive, 1, MPI_PACKET, processRank, ACK, MPI_COMM_WORLD, &status);
        printf("%d Student[%d](A:%d, R:%d) ready to enter safeplace\n", lamportClock, processRank, countStudentAcknowledges(studentAcknowledges), studentWineRequest);

        dealWithWinemaker();
        resetStudentAcknowledges(studentAcknowledges);

        printf("%d Student[%d](A:%d, R:%d) leaves safeplace\n", lamportClock, processRank, countStudentAcknowledges(studentAcknowledges), studentWineRequest);

        // Zakomentuj dla wersji z kartki
        // sendAcknowledgeToTheNextPendingStudent();

        // Z kartki
        sendAcknowledgeToAllPendingStudents();

        // Odblokuj wątek komunikacyjny
        sendPacket(0, processRank, REQ);
        requestsSent = false;
    }
}

void partyAndPlanAnotherParty() {
    studentWineRequest = rand() % maxWine + 1;
    sleep(studentWineRequest);
}

void sendRequestsToStudents(bool &requestsSent) {
    // Wyślij REQ do pozostałych studentów
    packetSend = (packet*) malloc(sizeof(packet));
    latestRequestLamportClock = lamportClock;
    incrementLamportClock();
    packetSend->lc = lamportClock;

    for (int i = WINEMAKER_COUNT; i < WINEMAKER_COUNT+STUDENT_COUNT; i++)
    {
        if (i != processRank) {            
            sendPacket(packetSend, i, REQ);
        }
    }
    printf("%d Student[%d](A:%d, R:%d) sends request for safeplace\n", lamportClock, processRank, countStudentAcknowledges(studentAcknowledges), studentWineRequest);

    free(packetSend);
    requestsSent = true;
}

void dealWithWinemaker() {
    chosenWinemakerId = chooseWinemaker();

    if(chosenWinemakerId != -1) {
        // Odbierz wino od wybranego winiarza
        int remainingWine = sendWineAmountToWinemaker(chosenWinemakerId);
        sendWineAmountUpdateToStudents(chosenWinemakerId, remainingWine);
    }
    else {
        // Oczekuj na kolejne oferty od winiarzy, bądź aktualizacje ofert od studentów
        MPI_Recv(&packetReceive, 1, MPI_PACKET, MPI_ANY_SOURCE, WINE_INFO, MPI_COMM_WORLD, &status);
        isReceivedLamportClockSmaller = packetReceive.lc < lamportClock;
        isReceivedLamportClockEqual = packetReceive.lc == lamportClock;
        lamportClock = max(lamportClock, packetReceive.lc) + 1;

        if(packetReceive.src >= WINEMAKER_COUNT) {
            handleWinemakerQueue();
        }
        else {
            handleWineInfo();
        }

        dealWithWinemaker();
    }
}

int chooseWinemaker() {
    std::vector<int> studentPositionsInQueue(STUDENT_COUNT, STUDENT_COUNT);
    std::vector<int> unavailableWinemakers;

    // Ustal pozycje studentów w kolejce
    for(int i = 0; i < STUDENT_COUNT; i++) {
        studentPositionsInQueue[i] = getStudentPositionInQueue(i);
    }

    // Wybierz pierwszego możliwego winiarza ze swojej kolejki
    if(studentPositionsInQueue[processRank-WINEMAKER_COUNT] == 0 && studentDecisionStructure[processRank-WINEMAKER_COUNT].capacity() > 0) {
        int i=0;
        for(int winemakerId : studentDecisionStructure[processRank-WINEMAKER_COUNT]) {
            if(wineOfferWineAmounts[winemakerId] > 0) {
                return winemakerId;
            }
            else {
                unavailableWinemakers.push_back(winemakerId);
            }
            i++;
        }
    }
    // Wyeliminuj z wyboru winiarzy, których wybrali studenci wcześniejsi w kolejce
    else  {
        int i = 0;
        for (int position : studentPositionsInQueue) {
            if(position >= studentDecisionStructure[i].capacity()) {
                continue;
            }
            else {
                unavailableWinemakers.push_back(studentDecisionStructure[i][position]);
            }
        }
        
    }

    // Wybierz winiarza z pozostałych, którzy zostaną po eliminacji przez studentów, którzy są wcześniej w kolejce
    for(int winemakerId : studentDecisionStructure[processRank - WINEMAKER_COUNT]) {
        if(std::find(unavailableWinemakers.begin(), unavailableWinemakers.end(), winemakerId) != unavailableWinemakers.end() && wineOfferWineAmounts[winemakerId] > 0) {
            return winemakerId;
        }
    }

    // Nie udało się wybrać winiarza
    return -1;
}

int getStudentPositionInQueue(int studentId) {
    int studentLamportClock = studentLamportClocks[studentId];
    int count = 0;

    for(int i = 0; i < STUDENT_COUNT; i++) {
        if(studentLamportClock < studentLamportClocks[i] || 
           (studentLamportClock == studentLamportClocks[i] && i < studentId)) {
            count++;
        }
    }

    return count;
}

int sendWineAmountToWinemaker(int winemakerId) {
    packetSend = (packet*) malloc(sizeof(packet));
    int wineToTake = min(studentWineRequest, wineOfferWineAmounts[winemakerId]);
    packetSend->data = wineToTake;
    studentWineRequest -= wineToTake;
    incrementLamportClock();
    packetSend->lc = lamportClock;

    wineOfferWineAmounts[winemakerId] -= wineToTake;
    sendPacket(packetSend, winemakerId, WINE_AMOUNT);
    printf("%d Student[%d](A:%d, R:%d) takes %d wine from Winemaker[%d]\n", lamportClock, processRank, countStudentAcknowledges(studentAcknowledges), studentWineRequest, wineToTake, winemakerId);
    
    free(packetSend);
    return wineOfferWineAmounts[winemakerId];
}

void sendWineAmountUpdateToStudents(int winemakerId, int wineAmount) {
    packetSend = (packet*) malloc(sizeof(packet));
    packetSend->lc = lamportClock;
    packetSend->wine = wineAmount;
    packetSend->data = winemakerId;

    for (int i = WINEMAKER_COUNT; i < WINEMAKER_COUNT+STUDENT_COUNT; i++)
    {
        if (i != processRank) {            
            sendPacket(packetSend, i, WINE_UPDATE);
        }
    }
    printf("%d Student[%d](A:%d, R:%d) sends update of Winemaker[%d]'s offer to students\n", lamportClock, processRank, countStudentAcknowledges(studentAcknowledges), studentWineRequest, winemakerId);

    free(packetSend);
}

void resetStudentAcknowledges(std::vector<int> &studentAcknowledges) {
    for (int i = 0; i < STUDENT_COUNT; i++)
    {
        studentAcknowledges[i] = 0;        
    }
}

void sendAcknowledgeToTheNextPendingStudent() {
    if(!pendingStudents.empty()) {
        packetSend = (packet*) malloc(sizeof(packet));
        incrementLamportClock();
        packetSend->lc = lamportClock;

        sendPacket(packetSend, pendingStudents[0], ACK);
        printf("%d Student[%d](A:%d, R:%d) sends acknowledge to Student[%d]<%d> (From queue)\n", lamportClock, processRank, countStudentAcknowledges(studentAcknowledges), studentWineRequest, pendingStudents[0], packetReceive.lc);

        pendingStudentsMutex.lock();
        pendingStudents.erase(pendingStudents.begin());
        pendingStudentsMutex.unlock();
        free(packetSend);
    }
}

void sendAcknowledgeToAllPendingStudents() {
    if(!pendingStudents.empty()) {
        packetSend = (packet*) malloc(sizeof(packet));
        incrementLamportClock();
        packetSend->lc = lamportClock;

        for(int studentId : pendingStudents) {
            sendPacket(packetSend, studentId, ACK);
            printf("%d Student[%d](A:%d, R:%d) sends acknowledge to Student[%d]<%d> (From queue)\n", lamportClock, processRank, countStudentAcknowledges(studentAcknowledges), studentWineRequest, studentId, packetReceive.lc);
        }

        pendingStudentsMutex.lock();
        pendingStudents.clear();
        pendingStudentsMutex.unlock();

        free(packetSend);
    }
}


void *startStudentCommThread(void *ptr) {
    while(true) {
        MPI_Recv(&packetReceive, 1, MPI_PACKET, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        if(packetReceive.src != processRank) {
            isReceivedLamportClockSmaller = packetReceive.lc < lamportClock;
            isReceivedLamportClockEqual = packetReceive.lc == lamportClock;
            lamportClock = max(lamportClock, packetReceive.lc) + 1;

            if(packetReceive.src >= WINEMAKER_COUNT) {
                studentLamportClocks[packetReceive.src] = packetReceive.lc;
            }

            switch(status.MPI_TAG) {
                case REQ:
                    // Zareaguj na request od studenta
                    handleStudentRequest();
                    break;

                case WINE_INFO:
                    if(packetReceive.src >= WINEMAKER_COUNT) {
                        // Zaktualizuj kolejkę odpowiedniego studenta w strukturze decyzyjnej
                        handleWinemakerQueue();
                    }
                    else {
                        // Dodaj Winiarza do swojej kolejki i zaktualizuj strukturę decyzyjną
                        handleWineInfo();
                    }
                    break;
                
                case ACK:
                    // Zaktualizuj acknowledge
                    handleStudentAcknowledge();
                    break;

                case WINE_UPDATE:
                    // Zaktualizuj informacje o ilości wina
                    handleWineUpdate();
                    break;

            }
        }
    }
}

void handleStudentRequest() {
    printf("%d Student[%d](A:%d, R:%d) receives request from Student[%d]<%d>\n", lamportClock, processRank, countStudentAcknowledges(studentAcknowledges), studentWineRequest, packetReceive.src, packetReceive.lc);

    if(isReceivedLamportClockSmaller || (isReceivedLamportClockEqual && packetReceive.src < processRank)) {
        sendStudentAcknowledge();
    }
    else {
        // Zakomentuj dla wersji z kartki
        // sendAcknowledgeToTheNextPendingStudent();

        appendStudentRequest();        
    }
}

void sendStudentAcknowledge() {
    packetSend = (packet*) malloc(sizeof(packet));
    incrementLamportClock();
    packetSend->lc = lamportClock;
    sendPacket(packetSend, packetReceive.src, ACK);
    printf("%d Student[%d](A:%d, R:%d) sends acknowledge to Student[%d]<%d> (normal)\n", lamportClock, processRank, countStudentAcknowledges(studentAcknowledges), studentWineRequest, packetReceive.src, packetReceive.lc);
}

void appendStudentRequest() {
    pendingStudentsMutex.lock();

    pendingStudents.push_back(packetReceive.src);
    printf("%d Student[%d](A:%d, R:%d) adds request from Student[%d]<%d> to pendingStudents\n", lamportClock, processRank, countStudentAcknowledges(studentAcknowledges), studentWineRequest, packetReceive.src, packetReceive.lc);

    pendingStudentsMutex.unlock();
}

void handleWinemakerQueue() {
    updateDecisionStructure(packetReceive.src-WINEMAKER_COUNT, packetReceive.data);
}

void updateDecisionStructure(int studentId, int winemakerId) {
    auto it = std::find(studentDecisionStructure[studentId].begin(), studentDecisionStructure[studentId].end(), winemakerId);
    int index = it - studentDecisionStructure[studentId].begin();

    if(it != studentDecisionStructure[studentId].end()) {
        studentDecisionStructure[studentId].erase(studentDecisionStructure[studentId].begin() + index);
    }
    studentDecisionStructure[studentId].push_back(winemakerId);
}

void handleWineInfo() {
    int winemakerId = packetReceive.src;
    int wineAmount = packetReceive.data;
    auto it = std::find(wineOfferWinemakerIds.begin(), wineOfferWinemakerIds.end(), winemakerId);
    int index = it - wineOfferWinemakerIds.begin();

    // Zaktualizuj istniejącą już ofertę i potem dodaj ją do końca kolejki od nowa
    if(it != wineOfferWinemakerIds.end()) {
        wineOfferWinemakerIds.erase(wineOfferWinemakerIds.begin() + index);
        wineOfferWineAmounts[winemakerId] = wineAmount;
    }

    wineOfferWinemakerIds.push_back(winemakerId);
    wineOfferWineAmounts[winemakerId] = wineAmount;

    printf("%d Student[%d](A:%d, R:%d) receives offer from Winemaker[%d]<%d>\n", lamportClock, processRank, countStudentAcknowledges(studentAcknowledges), studentWineRequest, packetReceive.src, packetReceive.lc);
    sendWinemakerOfferQueueToStudents();

    updateDecisionStructure(processRank-WINEMAKER_COUNT, winemakerId);
}

void sendWinemakerOfferQueueToStudents() {
    packetSend = (packet*) malloc(sizeof(packet));
    packetSend->lc = lamportClock;
    packetSend->data = packetReceive.src;

    for (int i = WINEMAKER_COUNT; i < WINEMAKER_COUNT+STUDENT_COUNT; i++)
    {
        if (i != processRank) {            
            sendPacket(packetSend, i, WINE_INFO);
        }
    }
    printf("%d Student[%d](A:%d, R:%d) sends his winemaker queue to students\n", lamportClock, processRank, countStudentAcknowledges(studentAcknowledges), studentWineRequest);

    free(packetSend);
}

void handleStudentAcknowledge() {
    if(packetReceive.lc > latestRequestLamportClock && packetReceive.lc > latestSafeplaceEntryLamportClock) {
        studentId = packetReceive.src-WINEMAKER_COUNT;
        studentAcknowledges[studentId] = 1;
        printf("%d Student[%d](A:%d, R:%d) received acknowledge from Student[%d]<%d>\n", lamportClock, processRank, countStudentAcknowledges(studentAcknowledges), studentWineRequest, packetReceive.src, packetReceive.lc);

        if (countStudentAcknowledges(studentAcknowledges) >= STUDENT_COUNT - 1) {
            latestSafeplaceEntryLamportClock = lamportClock;

            // Wyślij zgodę do wątku głównego na wejście do bezpiecznego miejsca
            sendPacket(0, processRank, ACK);

            // Zablokuj wątek komunikacyjny do momentu opuszczenia bezpiecznego miejsca
            MPI_Recv(&packetReceive, 1, MPI_PACKET, processRank, REQ, MPI_COMM_WORLD, &status);
        }

    }
}

int countStudentAcknowledges(std::vector<int> &studentAcknowledges) {
    int countAck = 0;

    for (int ack : studentAcknowledges) {
        if (ack) countAck++;
    }

    return countAck;
}

void handleWineUpdate() {
    printf("%d Student[%d](A:%d, R:%d) receives update from Student[%d] for Winemaker[%d]'s offer\n", lamportClock, processRank, countStudentAcknowledges(studentAcknowledges), studentWineRequest, packetReceive.src, packetReceive.data);
    int winemakerId = packetReceive.data;
    int wineAmount = packetReceive.wine;

    wineOfferWineAmounts[winemakerId] = wineAmount;
}
