#pragma once

#include <iostream>
#include <string>


class Date
{
private:
    int *day;
    int *month;
    int *year;

    bool checkDate(int d, int m, int y);

public:
    Date();
    Date(int d, int m, int y);
    Date(const Date &d);

    
    void setDate(int d, int m, int y);
    void setDay(int d);
    void setMonth(int m);
    void setYear(int y);

    int getDay() const;
    int getMonth() const;
    int getYear() const;
    Date getDate() const;
    std::string getDateString() const;
};