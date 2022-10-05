#include <string>
#include <iostream>

//Zad.2
class Samochod
{
private:
    float pojemnosc_baku;
    float poziom_paliwa;
    unsigned int liczba_kilometrow;
    std::string model;

    float spalanie;

public:
    //Zad.3 konstruktory
    Samochod();
    Samochod(float poj, std::string m);

    //gettery
    float getPojemnoscBaku();
    float getPoziomPaliwa();
    unsigned int getLiczbaKilometrow();
    std::string getModel();

    //settery
    void setPojemnoscBaku(float poj);
    void setPoziomPaliwa(float poz);
    void setLiczbaKilometrow(unsigned int km);
    void setModel(std::string m);

    //Zad4. Metody własne
    void jedz();
    void tankuj();
    void tankuj(float paliwo);

    //Zad.5/6
    operator bool () const;
    bool operator !() const;

    //Zad.7/8 Poniższa funkcja nie jest częścią klasy Samochod, jest spoza niej,
    //jej zaprzyjaźnienie umozliwia dostęp do prywatnych pól klasy Samochod za 
    //pomocą operatora "."
    friend std::ostream &operator << (std::ostream &os, const Samochod &samochod);

    //Zad.9-11 Słowo kluczowe "const" uniemożliwia metodzie modyfikację pól klasy,
    //pozwala jedynie na ich odczyt
    bool operator < (const Samochod &samochod) const;
    bool operator > (const Samochod &samochod) const;

    //Zad.15
    Samochod operator++(int);
    Samochod operator|=(const Samochod &samochod);
    Samochod operator+(const Samochod &samochod);
    Samochod operator,(const Samochod &samochod);
};