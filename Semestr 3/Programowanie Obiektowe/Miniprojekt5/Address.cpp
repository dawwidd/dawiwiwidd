#include "Address.h"

Address::Address():city(nullptr), street(nullptr), number(nullptr)
{
    city = new std::string;
    street = new std::string;
    number = new std::string;
}

Address::Address(std::string c, std::string s, std::string n)
{
    city = new std::string;
    street = new std::string;
    number = new std::string;

    while(true)
    {
        if(!checkAddress(c,s,n))
        {
            std::cout<<"Niepoprawny adres. Wprowadz ponownie: "<<std::endl;
            std::cin>>c>>s>>n;
            continue;
        }
        *city=c;
        *street=s;
        *number=n;
        break;
    }
}

Address::Address(const Address &a)
{
    city = new std::string;
    street = new std::string;
    number = new std::string; 
    
    *city=a.getCity();
    *street=a.getStreet();
    *number=a.getNumber();
}




bool Address::checkAddress(std::string c, std::string s, std::string n)
{
        for (int i = 0; i < c.size(); i++)
        {
            if (toupper(c[i]) < 'A' || toupper(c[i]) > 'Z')
            {
                return false;
            }
        }

        for (int i = 0; i < s.size(); i++)
        {
            if (toupper(s[i]) < 'A' || toupper(s[i]) > 'Z')
            {
                return false;
            }
        }

        for (int i = 0; i < n.size(); i++)
        {
            if (n[i] < '0' || n[i] > '9')
            {
                return false;
            }
        }
        return true;
}


void Address::setAddress(std::string c, std::string s, std::string n)
{
    while(true)
    {
        if(!checkAddress(c,s,n))
        {
            std::cout<<"Niepoprawny adres. Wprowadz ponownie: "<<std::endl;
            std::cin>>c>>s>>n;
            continue;
        }
        *city=c;
        *street=s;
        *number=n;
        break;
    }
}

void Address::setCity(std::string c)
{
    while(true)
    {
        if(!checkAddress(c,*street,*number))
        {
            std::cout<<"Niepoprawne miasto. Wprowadz ponownie: "<<std::endl;
            std::cin>>c;
            continue;
        }
        *city=c;
        break;
    }
}

void Address::setStreet(std::string s)
{
    while(true)
    {
        if(!checkAddress(*city,s,*number))
        {
            std::cout<<"Niepoprawna ulica. Wprowadz ponownie: "<<std::endl;
            std::cin>>s;
            continue;
        }
        *street=s;
        break;
    }
}

void Address::setNumber(std::string n)
{
    while(true)
    {
        if(!checkAddress(*city,*street,n))
        {
            std::cout<<"Niepoprawny numer. Wprowadz ponownie: "<<std::endl;
            std::cin>>n;
            continue;
        }
        *number=n;
        break;
    }
}



std::string Address::getCity() const
{
    return *city;
}

std::string Address::getStreet() const
{
    return *street;
}

std::string Address::getNumber() const
{
    return *number;
}

Address Address::getAddress() const
{
    return *this;
}

std::string Address::getAddressString() const
{
    return *city + " " + *street + " " + *number;
}