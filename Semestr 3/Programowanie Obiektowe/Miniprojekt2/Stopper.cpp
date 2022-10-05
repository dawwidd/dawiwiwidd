#include "Stopper.h"


Stopper::Stopper()
{
    total_time=0;
}


void Stopper::Start()
{
    start = high_resolution_clock::now();
}


void Stopper::Stop()
{
    end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end-start);
    total_time+=duration.count();
}


void Stopper::Reset()
{
    total_time=0;
}


void Stopper::Display()
{
    std::cout<<"Total time of execution: "<<std::fixed<<total_time/1000000.0<<"s"<<std::endl;
}
