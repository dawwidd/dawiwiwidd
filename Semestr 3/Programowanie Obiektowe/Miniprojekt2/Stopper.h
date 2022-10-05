#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <chrono>

using namespace std::chrono;

//Zad.30
class Stopper
{
private:
    high_resolution_clock::time_point start, end;
    double total_time;

public:
    Stopper();

    void Start();
    void Stop();
    void Reset();
    void Display();
};