#include "Student.h"


Student::Student():Oceny(nullptr)
{
    Oceny = new std::map<std::string, int>;
}

Student::Student(std::string n, std::string sn, Date dob, Address a)
{
    std::cout<<"Student conversion constructor"<<std::endl;
    Oceny = new std::map<std::string, int>;
    setName(n);
    setSurname(sn);
    setDateOfBirth(dob);
    setAddress(a);
}

Student::Student(const Student &s)
{
    std::cout<<"Student deep copy constructor"<<std::endl;
    Oceny = new std::map<std::string, int>;
    *Oceny = s.getMarks();
}

Student::~Student()
{
    // std::cout<<"Student Destrukszyn"<<getName()<<std::endl;
    delete Oceny;
}


void Student::addMark(std::string subject, int grade)
{
    Oceny->insert(std::pair<std::string, int>(subject, grade));
}

void Student::setMarks(std::map<std::string, int> O)
{
    (*Oceny)=O;
}


int Student::getMark(std::string subject) const
{
    return (*Oceny)[subject];
}

std::map<std::string, int> Student::getMarks() const
{
    return *Oceny;
}


void Student::getMarksList()
{
    std::map<std::string, int>::iterator itr;
    for(itr = Oceny->begin(); itr != Oceny->end(); itr++)
    {
        std::cout<<itr->first<<"   "<<itr->second<<std::endl;
    }
}


void Student::displayInfo()
{
    std::cout<<getName()+" "+getSurname()+" "+getDateOfBirth()+" "+getAddress()<<std::endl;
    getMarksList();
}