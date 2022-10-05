#pragma once

#include <iostream>
#include <string>


//Zad.24
class Logger
{
private:
    bool debug; //Zad.28

public:
    Logger() = default;
    Logger(bool dbg); //Zad.28/29 Aby można było skompilować program należy przy konstruktorach
                      //klasy JednorekiBandyta wywołać konstruktor Logger z odpowiednim parametrem
    
    void log(std::string txt);

};