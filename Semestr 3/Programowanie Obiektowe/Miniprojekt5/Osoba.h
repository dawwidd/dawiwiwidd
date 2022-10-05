#pragma once

#include <iostream>
#include <string>
#include <memory>
#include "Address.h"
#include "Date.h"

//Zadanie 4a
class Osoba
{
private:
    std::string *name, *surname;
    Date *dateOfBirth;
    Address *address;
    
public:
    Osoba();
    Osoba(std::string n, std::string sn, Date dob, Address a);
    Osoba(const Osoba &o);

    virtual ~Osoba();

    void setName(std::string n);
    void setSurname(std::string sn);
    void setDateOfBirth(Date dob);
    void setAddress(Address a);

    std::string getName() const;
    std::string getSurname() const;
    std::string getDateOfBirth() const;
    std::string getAddress() const;


    //virtual void displayInfo()=0; //Zad.18,19 Taka deklaracja funkcji powoduje, że klasa jest czysto virtualna i nie można utworzyć jej instancji
    virtual void displayInfo();

};