#pragma once

#include "Osoba.h"
#include <vector>

//Zadanie 4c
class Pracownik : public Osoba
{
private:
    std::vector<std::string> *Subjects;

public:
    Pracownik();
    Pracownik(std::string n, std::string sn, Date dob, Address a);
    Pracownik(const Pracownik &p);

    ~Pracownik();

    void addSubject(std::string s);
    void removeSubject(std::string s);

    bool checkSubject(std::string s);

    void setSubjects(std::vector<std::string> S);

    std::vector<std::string> getSubjects() const;

    void displayInfo();
};