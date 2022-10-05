#include "Date.h"


Date::Date():day(nullptr), month(nullptr), year(nullptr)
{
    day = new int;
    month = new int;
    year = new int;
}

Date::Date(int d, int m, int y)
{
    day = new int;
    month = new int;
    year = new int;

    while(true)
    {
        if(!checkDate(d,m,y))
        {
            std::cout<<"Niepoprawna data. Wprowadz ponownie: "<<std::endl;
            std::cin>>d>>m>>y;
            continue;
        }
        *day=d;
        *month=m;
        *year=y;
        break;
    }
}

Date::Date(const Date &d)
{
    day = new int;
    month = new int;
    year = new int;

    *day=d.getDay();
    *month=d.getMonth();
    *year=d.getYear();
}



bool Date::checkDate(int d, int m, int y)
{
    if(y>=1970)
    {
        if(d>=1 && d<=31 && (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)) return true;
        else if(d>=1 && d<=30 && (m == 4 || m == 6 || m == 9 || m == 11)) return true;
        else if(d>=1 && d<=28 && m == 2) return true;
        else if(d>=1 && d<=29 && (y%4 == 0 && y%100 != 0)) return true;
        else return false;
    }
    return false;
}

void Date::setDate(int d, int m, int y)
{
    while(true)
    {
        if(!checkDate(d,m,y))
        {
            std::cout<<"Niepoprawna data. Wprowadz ponownie: "<<std::endl;
            std::cin>>d>>m>>y;
            continue;
        }
        *day=d;
        *month=m;
        *year=y;
        break;
    }
}

void Date::setDay(int d)
{
    while(true)
    {
        if(!checkDate(d,*month,*year))
        {
            std::cout<<"Niepoprawny dzien. Wprowadz ponownie: "<<std::endl;
            std::cin>>d;
            continue;
        }
        *day=d;
        break;
    }
}

void Date::setMonth(int m)
{
    while(true)
    {
        if(!checkDate(*day, m, *year))
        {
            std::cout<<"Niepoprawny miesiac. Wprowadz ponownie: "<<std::endl;
            std::cin>>m;
            continue;
        }
        *month=m;
        break;
    }
}

void Date::setYear(int y)
{
    while(true)
    {
        if(!checkDate(*day,*month,y))
        {
            std::cout<<"Niepoprawny rok. Wprowadz ponownie: "<<std::endl;
            std::cin>>y;
            continue;
        }
        *year=y;
        break;
    }
}


int Date::getDay() const
{
    return *day;
}

int Date::getMonth() const
{
    return *month;
}

int Date::getYear() const
{
    return *year;
}

Date Date::getDate() const
{
    return *this;
}

std::string Date::getDateString() const
{
    return std::to_string(*day) + "." + std::to_string(*month) + "." + std::to_string(*year);
}