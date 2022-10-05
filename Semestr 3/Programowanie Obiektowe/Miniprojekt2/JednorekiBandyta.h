#pragma once

#include "Logger.h"
#include "Stopper.h"

#include <iostream>

//Zad.32 Wielodziedziczenie może doprowadzić do wielokrotnego powtórzenia się
//tej samej informacji w klasie dziedziczącej. Jednym z rozwiązań tego problemu jest zastosowanie
//dziedziczenia wirtualnego, które umożliwi uwspólnienie poszczególnych części.
//Rozwiązanie to zastosowano w Javie, z użyciem interfejsów.

class JednorekiBandyta : public Logger /* Zad.25 */, public Stopper /* Zad.31 */
{
private:
    //Zad.7
    double *cost; //koszt pojedynczej gry
    double *rewardPercentage; //procent kosztu przechodzący do puli nagród
    double *winProbability; //prawdopodobieństwo wygranej
    double *winningPool; //pula nagród
    int *gameCount; //liczba rozegranych gier

    double *winRate; //stosunek ilości zwycięstw do rozegranych gier
    double *wins; //ilość zwycięstw

    static int ID;
    int thisID;

public:
    //konstruktory
    JednorekiBandyta();
    JednorekiBandyta(double c, double rP, double wP);
    JednorekiBandyta(const JednorekiBandyta &jb);
    JednorekiBandyta(JednorekiBandyta &&jb);
    ~JednorekiBandyta();

    //settery
    void setCost(double x);
    void setRewardPercentage(double x);
    void setWinProbability(double x);
    void setWinningPool(double x);
    void setGameCount(int x);
    void setWinRate(double x);
    void setWins(double x);

    //gettery
    double getCost() const;
    double getRewardPercentage() const;
    double getWinProbability() const;
    double getWinningPool() const;
    int    getGameCount() const;
    double getWinRate() const;
    double getWins() const;
    
    //Zad.13 Metody funkcjonalne
    void play();

    void calcWinRate();
    double getWinRate();
};