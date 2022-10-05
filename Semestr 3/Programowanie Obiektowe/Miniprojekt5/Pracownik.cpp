#include "Pracownik.h"
#include <algorithm>
#include <bits/stdc++.h>


Pracownik::Pracownik()
{
    Subjects = new std::vector<std::string>;
}

Pracownik::Pracownik(std::string n, std::string sn, Date dob, Address a)
{
    std::cout<<"Pracownik conversion constructor"<<std::endl;
    Subjects = new std::vector<std::string>;

    setName(n);
    setSurname(sn);
    setDateOfBirth(dob);
    setAddress(a);
}

Pracownik::Pracownik(const Pracownik &p)
{
    std::cout<<"Pracownik deep copy constructor"<<std::endl;
    Subjects = new std::vector<std::string>;
    Subjects = p.Subjects;
}

Pracownik::~Pracownik()
{
    // std::cout<<"Pracownik Destrukszyn"<<getName()<<std::endl;
    delete Subjects;
}


void Pracownik::addSubject(std::string s)
{
    if(!(std::find(Subjects->begin(), Subjects->end(), s)!=Subjects->end()))
    {
        Subjects->push_back(s);
    }
}

void Pracownik::removeSubject(std::string s)
{
    std::vector<std::string>::iterator itr;

    for(itr=Subjects->begin(); itr!=Subjects->end(); ++itr)
    {
        if(*itr==s)
        {
            Subjects->erase(itr);
            break;
        }
    }
}

bool Pracownik::checkSubject(std::string s)
{
    if(std::find(Subjects->begin(), Subjects->end(), s)!=Subjects->end())
    {
        return true;
    }
    return false;
}

void Pracownik::setSubjects(std::vector<std::string> S)
{
    *Subjects = S;
}


std::vector<std::string> Pracownik::getSubjects() const
{
    return *Subjects;
}


void Pracownik::displayInfo()
{
    std::cout<<getName()+" "+getSurname()+" "+getDateOfBirth()+" "+getAddress()<<std::endl;

    for(int i=0; i<Subjects->size(); i++)
    {
        std::cout<<(*Subjects)[i]<<std::endl;
    }
}