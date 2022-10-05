#pragma once

#include "Osoba.h"
#include <map>

//Zadanie 4b
class Student : public Osoba
{
private:   
    std::map<std::string, int> *Oceny;

public:
    Student();
    Student(std::string n, std::string sn, Date dob, Address a);
    Student(const Student &s);

    ~Student();

    void addMark(std::string subject, int grade);
    void setMarks(std::map<std::string, int> O);

    int getMark(std::string subject) const;
    std::map<std::string, int> getMarks() const;
    void getMarksList();
    
    void displayInfo();
};