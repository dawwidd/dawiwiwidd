#include "Osoba.h"


Osoba::Osoba():name(nullptr), surname(nullptr),
dateOfBirth(nullptr), address(nullptr)
{
    // std::cout<<"Osoba default constructor"<<std::endl;
    name = new std::string;
    surname = new std::string;
    dateOfBirth = new Date;
    address = new Address;
}

Osoba::Osoba(std::string n, std::string sn, Date dob, Address a):
name(nullptr), surname(nullptr), dateOfBirth(nullptr), address(nullptr)
{
    // std::cout<<"Osoba conversion constructor"<<std::endl;
    
    name = new std::string;
    surname = new std::string;
    dateOfBirth = new Date;
    address = new Address;

    *name=n;
    *surname=sn;
    *dateOfBirth=dob;
    *address=a;
}

Osoba::Osoba(const Osoba &o)
{
    // std::cout<<"Osoba deep copy constructor"<<std::endl;
    
    name = new std::string;
    surname = new std::string;
    dateOfBirth = new Date;
    address = new Address;

    *name = o.getName();
    *surname=o.getSurname();
    *dateOfBirth=o.dateOfBirth->getDate();
    *address=o.address->getAddress();
}

Osoba::~Osoba()
{
    // std::cout<<"Destrukszyn"<<getName()<<std::endl;
    delete name;
    delete surname;
    delete dateOfBirth;
    delete address;
}


void Osoba::setName(std::string n)
{
    *name=n;
}

void Osoba::setSurname(std::string sn)
{
    *surname=sn;
}

void Osoba::setDateOfBirth(Date dob)
{
    *dateOfBirth = dob;
}

void Osoba::setAddress(Address a)
{
    *address = a;
}


std::string Osoba::getName() const
{
    return *name;
}

std::string Osoba::getSurname() const
{
    return *surname;
}

std::string Osoba::getDateOfBirth() const
{
    return dateOfBirth->getDateString();
}

std::string Osoba::getAddress() const
{
    return address->getAddressString();
}


void Osoba::displayInfo()
{
    std::cout<<getName()+" "+getSurname()+" "+getDateOfBirth()+" "+getAddress()<<std::endl;
}