#include "winemaker.h"

std::mutex safeplaceMutex;
std::mutex pendingWinemakersMutex;

void winemakerMainLoop() {
    bool requestsSent = false;

    srand(time(NULL)*processRank);
    while(true) {
        if (!requestsSent) {
            produceWine();
            sendSafeplaceRequests(requestsSent);
        }

        // Zablokuj wątek do momentu otrzymania zgody na wejście do bezpiecznego miejsca
        MPI_Recv(&packetReceive, 1, MPI_PACKET, processRank, ACK, MPI_COMM_WORLD, &status);
        printf("%d Winemaker[%d](A:%d, W:%d) enters safeplace\n", lamportClock, processRank, countAcknowledges(winemakersAcknowledges), wine);
        
        // Dopóki jest wino pozostań w bezpiecznym miejscu i przeprowadzaj transakcje
        while(wine > 0) {
            sendWineInfoToStudents();
            printf("%d Winemaker[%d](A:%d, W:%d) awaits for students to take wine\n", lamportClock, processRank, countAcknowledges(winemakersAcknowledges), wine);

            MPI_Recv(&packetReceive, 1, MPI_PACKET, MPI_ANY_SOURCE, WINE_AMOUNT, MPI_COMM_WORLD, &status);

            isReceivedLamportClockSmaller = packetReceive.lc < lamportClock;
            isReceivedLamportClockEqual = packetReceive.lc == lamportClock;
            lamportClock = max(lamportClock, packetReceive.lc) + 1;

            wine -= packetReceive.data;
            printf("%d Winemaker[%d](A:%d, W:%d) gives %d wine to Student[%d]<%d>\n", lamportClock, processRank, countAcknowledges(winemakersAcknowledges), wine, packetReceive.data, packetReceive.src, packetReceive.lc);
        }
        
        printf("%d Winemaker[%d](A:%d, W:%d) leaves safeplace\n", lamportClock, processRank, countAcknowledges(winemakersAcknowledges), wine);

        // Zakomentuj dla wersji z kartki
        // sendAcknowledgeToTheNextPendingWinemaker();
        
        // Z kartki, działa, ale gorzej niż rozwiązanie wyżej (bywa, że winiarze wchodzą do zajętego bezpiecznego miejsca, lub dochodzi do zagłodzenia i zablokowania procesów)
        sendAcknowledgeToAllPendingWinemakers();

        // Odblokuj wątek komunikacyjny
        sendPacket(0, processRank, REQ);
        requestsSent = false;
    }
}

void produceWine() {
    wine = rand() % maxWine + 1;
    sleep(wine);
}

void sendSafeplaceRequests(bool &requestsSent) {
    packetSend = (packet*) malloc(sizeof(packet));
    latestRequestLamportClock = lamportClock;
    incrementLamportClock();
    packetSend->lc = lamportClock;

    for (int i = 0; i < WINEMAKER_COUNT; i++)
    {
        if (i != processRank) {
            sendPacket(packetSend, i, REQ);
        }
    }
    printf("%d Winemaker[%d](A:%d, W:%d) sends request for safeplace\n", lamportClock, processRank, countAcknowledges(winemakersAcknowledges), wine);

    free(packetSend);
    requestsSent = true;
}

void sendWineInfoToStudents() {
    packetSend = (packet*) malloc(sizeof(packet));
    packetSend->lc = lamportClock;
    packetSend->data = wine;

    printf("%d Winemaker[%d](A:%d, W:%d) sends offer for %d wine to students\n", lamportClock, processRank, countAcknowledges(winemakersAcknowledges), wine, wine);

    for (int i = WINEMAKER_COUNT; i < WINEMAKER_COUNT+STUDENT_COUNT; i++)
    {
        sendPacket(packetSend, i, WINE_INFO);
    }
    free(packetSend);
}

void sendAcknowledgeToTheNextPendingWinemaker() {
    if(!pendingWinemakers.empty()) {
        packetSend = (packet*) malloc(sizeof(packet));
        incrementLamportClock();
        packetSend->lc = lamportClock;

        sendPacket(packetSend, pendingWinemakers[0], ACK);
        printf("%d Winemaker[%d](A:%d, W:%d) sends acknowledge to Winemaker[%d]<%d> (From queue)\n", lamportClock, processRank, countAcknowledges(winemakersAcknowledges), wine, pendingWinemakers[0], packetReceive.lc);

        pendingWinemakers.erase(pendingWinemakers.begin());
        free(packetSend);
    }
}

// Z kartki, działa gorzej od rozwiązania wyżej
void sendAcknowledgeToAllPendingWinemakers() {
    if(!pendingWinemakers.empty()) {
        packetSend = (packet*) malloc(sizeof(packet));
        incrementLamportClock();
        packetSend->lc = lamportClock;

        for(int winemakerId : pendingWinemakers) {
            sendPacket(packetSend, winemakerId, ACK);
            printf("%d Winemaker[%d](A:%d, W:%d) sends acknowledge to Winemaker[%d]<%d> (From queue)\n", lamportClock, processRank, countAcknowledges(winemakersAcknowledges), wine, winemakerId, packetReceive.lc);
        }

        pendingWinemakers.clear();

        free(packetSend);
    }
}

void *startWinemakerCommThread(void *ptr) {
    while (true) {
        MPI_Recv(&packetReceive, 1, MPI_PACKET, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        if(packetReceive.src != processRank) {

            isReceivedLamportClockSmaller = packetReceive.lc < lamportClock;
            isReceivedLamportClockEqual = packetReceive.lc == lamportClock;
            lamportClock = max(lamportClock, packetReceive.lc) + 1;

            switch (status.MPI_TAG) {
                case REQ:
                    // Zareaguj na request od winiarza
                    handleSafeplaceRequest();
                    break;

                case ACK:
                    // Zaktualizuj acknowledge
                    handleWinemakerAcknowledge();
                    break;
                
                default:
                    break;
            }
        }
    }
}

void handleSafeplaceRequest() {
    printf("%d Winemaker[%d](A:%d, W:%d) receives request from Winemaker[%d]<%d>\n", lamportClock, processRank, countAcknowledges(winemakersAcknowledges), wine, packetReceive.src, packetReceive.lc); 

    if (isReceivedLamportClockSmaller || (isReceivedLamportClockEqual && packetReceive.src < processRank)) {
        sendWinemakerAcknowledge();
    }
    else {
        // Zakomentuj dla wersji z kartki
        // sendAcknowledgeToTheNextPendingWinemaker();

        if(!std::count(pendingWinemakers.begin(), pendingWinemakers.end(), packetReceive.src)) {
            pendingWinemakers.push_back(packetReceive.src);
            printf("%d Winemaker[%d](A:%d, W:%d) adds request from Winemaker[%d]<%d> to pending winemakers\n", lamportClock, processRank, countAcknowledges(winemakersAcknowledges), wine, packetReceive.src, packetReceive.lc);
        }
    }
}

void sendWinemakerAcknowledge() {
    packetSend = (packet*) malloc(sizeof(packet));
    incrementLamportClock();
    packetSend->lc = lamportClock;
    sendPacket(packetSend, packetReceive.src, ACK);
    printf("%d Winemaker[%d](A:%d, W:%d) sends acknowledge to Winemaker[%d]<%d> (normal)\n", lamportClock, processRank, countAcknowledges(winemakersAcknowledges), wine, packetReceive.src, packetReceive.lc);
}

void handleWinemakerAcknowledge() {
    if(packetReceive.lc > latestRequestLamportClock && packetReceive.lc > latestSafeplaceEntryLamportClock) {
        winemakersAcknowledges[packetReceive.src] = 1;
        printf("%d Winemaker[%d](A:%d, W:%d) receives acknowledge from Winemaker[%d]<%d>\n", lamportClock, processRank, countAcknowledges(winemakersAcknowledges), wine, packetReceive.src, packetReceive.lc);

        if (countAcknowledges(winemakersAcknowledges) >= WINEMAKER_COUNT - SAFEPLACE_COUNT) {
            latestSafeplaceEntryLamportClock = lamportClock;

            // Wyślij zgodę do wątku głównego na wejście do bezpiecznego miejsca
            sendPacket(0, processRank, ACK);

            // Zablokuj wątek komunikacyjny do momentu opuszczenia bezpiecznego miejsca
            MPI_Recv(&packetReceive, 1, MPI_PACKET, processRank, REQ, MPI_COMM_WORLD, &status);
            resetAcknowledges(winemakersAcknowledges);
        }
    }
}

int countAcknowledges(std::vector<int> &winemakersAcknowledges) {
    int countAck = 0;

    for (int ack : winemakersAcknowledges) {
        if (ack) countAck++;
    }

    return countAck;
}

void resetAcknowledges(std::vector<int> &winemakersAcknowledges) {
    for (int i = 0; i < WINEMAKER_COUNT; i++) {
        winemakersAcknowledges[i] = 0;        
    }
}
