#include "main.h"
#include "winemaker.h"
#include "student.h"

int processSize, processRank;
MPI_Datatype MPI_PACKET;
pthread_t winemakerCommThread, studentCommThread;
int maxWine = 10;
int wine;
int studentWineRequest;
int lamportClock;
std::mutex lamportClockMutex;
int latestRequestLamportClock = 0;
int latestSafeplaceEntryLamportClock = 0;

int winemakerStatus;
int studentStatus;

std::vector<int> pendingWinemakers;
std::vector<int> winemakersAcknowledges(WINEMAKER_COUNT);

std::vector<int> pendingStudents;
std::vector<int> studentAcknowledges(STUDENT_COUNT);

std::vector<int> studentWinemakersQueue(WINEMAKER_COUNT);
std::vector<std::vector<int>> studentDecisionStructure(STUDENT_COUNT, std::vector<int>());

// studentSafePlaceQueue[process_number][0: student_index/1: lamport_clock]
std::vector<std::vector<int>> studentSafePlaceQueue(STUDENT_COUNT, std::vector<int>(2));

MPI_Status status;
packet packetReceive;
packet *packetSend;
bool isReceivedLamportClockSmaller;
bool isReceivedLamportClockEqual;

int main(int argc, char **argv) {

    initMpi(&argc, &argv);  

    run();

    finalize();

    return 0;
}

void initMpi(int *argc, char ***argv) {
    int provided;
    MPI_Init_thread(argc, argv, MPI_THREAD_MULTIPLE, &provided);
    check_thread_support(provided);

    const int nitems=3; /* bo packet ma trzy pola */
    int       blocklengths[3] = {1,1,1};
    MPI_Datatype types[3] = {MPI_INT, MPI_INT, MPI_INT};

    MPI_Aint     offsets[3]; 
    offsets[0] = offsetof(packet, lc);
    offsets[1] = offsetof(packet, src);
    offsets[2] = offsetof(packet, data);

    MPI_Type_create_struct(nitems, blocklengths, offsets, types, &MPI_PACKET);
    MPI_Type_commit(&MPI_PACKET);

    MPI_Comm_rank(MPI_COMM_WORLD, &processRank);
    MPI_Comm_size(MPI_COMM_WORLD, &processSize);

    lamportClock = processRank;
}

void check_thread_support(int provided)
{
    // printf("THREAD SUPPORT: chcemy %d. Co otrzymamy?\n", provided);
    switch (provided) {
        case MPI_THREAD_SINGLE: 
            // printf("Brak wsparcia dla wątków, kończę\n");
            /* Nie ma co, trzeba wychodzić */
            fprintf(stderr, "Brak wystarczającego wsparcia dla wątków - wychodzę!\n");
            MPI_Finalize();
            exit(-1);
            break;
        case MPI_THREAD_FUNNELED: 
            printf("tylko te wątki, ktore wykonaly mpi_init_thread mogą wykonać wołania do biblioteki mpi\n");
	        break;
        case MPI_THREAD_SERIALIZED: 
            /* Potrzebne zamki wokół wywołań biblioteki MPI */
            printf("tylko jeden watek naraz może wykonać wołania do biblioteki MPI\n");
	        break;
        case MPI_THREAD_MULTIPLE: 
            // printf("Pełne wsparcie dla wątków\n"); /* tego chcemy. Wszystkie inne powodują problemy */
	        break;
        default: 
            printf("Nikt nic nie wie\n");
    }
}

void run() {

    if(isWinemaker()) {
        pthread_create(&winemakerCommThread, NULL, startWinemakerCommThread, 0);
        winemakerMainLoop();
    }
    else {
        pthread_create(&studentCommThread, NULL, startStudentCommThread, 0);
        studentMainLoop();
    }
}

int isWinemaker() {
    int isWinemaker = processRank >= 0 && processRank < WINEMAKER_COUNT;
    return isWinemaker;
}

void sendPacket(packet *pkt, int destination, int tag) {
    int freepkt = 0;
    if (pkt == 0)
    {
        pkt = (packet*) malloc(sizeof(packet));
        freepkt = 1;
    }

    pkt->src = processRank;
    // pkt->lc = lamportClock;
    MPI_Send(pkt, 1, MPI_PACKET, destination, tag, MPI_COMM_WORLD);

    if (freepkt) {
        free(pkt);
    }
    
}

void finalize() {
    if(isWinemaker()) {
        pthread_join(winemakerCommThread, NULL);
    }
    else {
        pthread_join(studentCommThread, NULL);
    }

    MPI_Type_free(&MPI_PACKET);
    MPI_Finalize();
}

int max(int x, int y) {
    return x > y ? x : y;
}

int min(int x, int y) {
    return x < y ? x : y;
}

void debug(std::string message) {
    printf("[DEBUG] %s\n", message.c_str());
}

std::string getVectorString(std::string title, std::vector<int> &vector) {
    std::string result = "";
    result += title + ": [";

    for(int i = 0; i < vector.capacity(); i++) {
        result += std::to_string(vector[i]) + ", ";
    }

    result += "]\n";

    return result;
}

void incrementLamportClock() {
    lamportClockMutex.lock();
    lamportClock++;
    lamportClockMutex.unlock();
}