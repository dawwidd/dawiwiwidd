#include "Logger.h"
#include <ctime>


Logger::Logger(bool dbg)
{
    debug=dbg;
}

void Logger::log(std::string txt)
{
    time_t now = time(0);
    char* dt = ctime(&now);

    if(debug) std::cout<<dt<<txt<<std::endl; 
}

