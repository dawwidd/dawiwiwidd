#pragma once

#include <iostream>
#include <string>


class Address
{
private:
    std::string *city, *street, *number;
    bool checkAddress(std::string c, std::string s, std::string n);
    
public:
    Address();
    Address(std::string c, std::string s, std::string n);
    Address(const Address &a);


    void setAddress(std::string c, std::string s, std::string n);
    void setCity(std::string c);
    void setStreet(std::string s);
    void setNumber(std::string n);

    std::string getCity() const;
    std::string getStreet() const;
    std::string getNumber() const;
    Address getAddress() const;
    std::string getAddressString() const;
};