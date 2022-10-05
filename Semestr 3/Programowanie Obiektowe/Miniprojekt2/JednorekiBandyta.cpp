#include "JednorekiBandyta.h"


//Zad.8 Konstruktor domyślny
JednorekiBandyta::JednorekiBandyta(): Logger(true), //Zad.29
cost(nullptr), rewardPercentage(nullptr), winProbability(nullptr),
winningPool(nullptr), gameCount(nullptr), winRate(nullptr), wins(nullptr)
{
    log("Default constructor"); //Zad.27
    thisID = ++ID;

    cost = new double;
    rewardPercentage = new double;
    winProbability = new double;
    winningPool = new double;
    gameCount = new int;
    winRate = new double;
    wins = new double;
}


//Zad.12 Konstruktor konwertujący
JednorekiBandyta::JednorekiBandyta(double c, double rP, double wP): Logger(true), //Zad.29
cost(nullptr), rewardPercentage(nullptr), winProbability(nullptr),
winningPool(nullptr), gameCount(nullptr), winRate(nullptr), wins(nullptr)
{
    log("Conversion constructor"); //Zad.27
    thisID = ++ID;

    cost = new double;
    *cost = c;

    rewardPercentage = new double;
    *rewardPercentage = rP;

    winProbability = new double;
    *winProbability = wP;

    winningPool = new double;
    *winningPool = 0.0f;

    gameCount = new int;
    *gameCount = 0;

    winRate = new double;
    *winRate = 0.0f;

    wins = new double;
    *wins = 0.0f;
}


//Zad.10 Konstruktor kopiujący
JednorekiBandyta::JednorekiBandyta(const JednorekiBandyta &jb): Logger(true) //Zad.29
{
    log("Deep copy constructor"); //Zad.27
    thisID = ++ID;

    cost = new double;
    rewardPercentage = new double;
    winProbability = new double;
    winningPool = new double;
    gameCount = new int;
    winRate = new double;
    wins = new double;

    *cost = jb.getCost();
    *rewardPercentage = jb.getRewardPercentage();
    *winProbability = jb.getWinProbability();
    *winningPool = jb.getWinningPool();
    *gameCount = jb.getGameCount();
    *winRate = jb.getWinRate();
    *wins = jb.getWins();
}


//Zad.11 Konstruktor przenoszący
JednorekiBandyta::JednorekiBandyta(JednorekiBandyta &&jb): Logger(true) //Zad.29
{
    log("Move constructor"); //Zad.27
    thisID = ++ID;

    cost = jb.cost;
    rewardPercentage = jb.rewardPercentage;
    winProbability = jb.winProbability;
    winningPool = jb.winningPool;
    gameCount = jb.gameCount;
    winRate = jb.winRate;
    wins = jb.wins;

    jb.cost = nullptr;
    jb.rewardPercentage = nullptr;
    jb.winProbability = nullptr;
    jb.winningPool = nullptr;
    jb.gameCount = nullptr;
    jb.winRate = nullptr;
    jb.wins = nullptr;
}


//Zad.9 Destruktor
JednorekiBandyta::~JednorekiBandyta()
{
    log("Destructor"); //Zad.27
    delete cost;
    delete rewardPercentage;
    delete winProbability;
    delete winningPool;
    delete gameCount;
    delete winRate;
    delete wins;
}


//Zainicjalizowanie zmiennej statycznej ID
int JednorekiBandyta::ID = 0;


//settery
void JednorekiBandyta::setCost(double x){*cost=x;}
void JednorekiBandyta::setRewardPercentage(double x){*rewardPercentage = x;}
void JednorekiBandyta::setWinProbability(double x){*winProbability = x;}
void JednorekiBandyta::setWinningPool(double x){ *winningPool=x; }
void JednorekiBandyta::setGameCount(int x){ *gameCount=x; }
void JednorekiBandyta::setWinRate(double x){ *winRate=x; }
void JednorekiBandyta::setWins(double x){ *wins=x; }


//gettery
double JednorekiBandyta::getCost() const{ return *cost; }
double JednorekiBandyta::getRewardPercentage() const{return *rewardPercentage;}
double JednorekiBandyta::getWinProbability() const{return *winProbability;}
double JednorekiBandyta::getWinningPool() const{return *winningPool;}
int    JednorekiBandyta::getGameCount() const{return *gameCount;}
double JednorekiBandyta::getWinRate() const{return *winRate;}
double JednorekiBandyta::getWins() const{return *wins;}


//Zad.13 Metody funkcjonalne
void JednorekiBandyta::play()
{
    Start();       //Zad.31
    log("play()"); //Zad.27
    (*gameCount)++;
    (*winningPool)+= (*rewardPercentage) * (*cost) / 100.0f; //obliczenie sumy przechodzącej do puli nagród
    int rnd = rand()%(int(1.0/ (*winProbability))); //generowanie losowej liczby
    if(rnd==0){
        //std::cout<<"You win "<<*winningPool<<"!"<<std::endl;
        *winningPool = 0;
        (*wins)++;
    }
    //else{std::cout<<"You lose!"<<std::endl;}
    Stop();  //Zad.31
}


void JednorekiBandyta::calcWinRate()
{
    Start(); //Zad.31
    log("calcWinRate()"); //Zad.27
    *winRate=100.0f* (*wins)/ (*gameCount);
    Stop(); //Zad.31
}


double JednorekiBandyta::getWinRate(){return *winRate;}