#include "Samochod.hpp"


//Konstruktory (Zad.3)
Samochod::Samochod()
{
    pojemnosc_baku = 100.0;
    poziom_paliwa = 100.0;
    liczba_kilometrow = 100;
    model = "Default model";
    spalanie=5.0;
}

Samochod::Samochod(float poj, std::string m)
{
    this->model = m;
    this->pojemnosc_baku = poj;
    poziom_paliwa = 100.0;
    liczba_kilometrow = 100;
    spalanie=5.0;
}


//Gettery
float Samochod::getPojemnoscBaku()
{
    return pojemnosc_baku;
}

float Samochod::getPoziomPaliwa()
{
    return poziom_paliwa;
}

unsigned int Samochod::getLiczbaKilometrow()
{
    return liczba_kilometrow;
}

std::string Samochod::getModel()
{
    return model;
}


//Settery
void Samochod::setPojemnoscBaku(float poj)
{
    pojemnosc_baku=poj;
}

void Samochod::setPoziomPaliwa(float poz)
{
    poziom_paliwa=poz;
}

void Samochod::setLiczbaKilometrow(unsigned int km)
{
    liczba_kilometrow=km;
}

void Samochod::setModel(std::string m)
{
    model=m;
}


//Zad.4 Metody własne
//Samochod jedzie, nalicza kilometry i spala paliwo
void Samochod::jedz()
{
    liczba_kilometrow++;
    poziom_paliwa-=spalanie/100.0;    
}

//Tankowanie do pełna
void Samochod::tankuj()
{
    this->setPoziomPaliwa(getPojemnoscBaku());
}

//Tankowanie okreslonej ilosci paliwa
void Samochod::tankuj(float paliwo)
{
    float ile_dolac;
    (ile_dolac = this->getPoziomPaliwa()+paliwo)<=this->getPojemnoscBaku() 
    ? this->setPoziomPaliwa(ile_dolac) : this->tankuj();
}


//Przeciążenia operatorów
//Zad.5
Samochod::operator bool () const
{
    return (this->model!="")&&(this->pojemnosc_baku>0);
}

bool Samochod::operator !() const
{
    return !((this->model!="")&&(this->pojemnosc_baku>0));
}

//Zad.7/8
std::ostream &operator << (std::ostream &os, const Samochod& samochod)
{
    os << samochod.model <<" "<< samochod.poziom_paliwa<<"\n";
    return os;
}

//Zad.9
bool Samochod::operator < (const Samochod &samochod) const
{
    return this->model < samochod.model;
}

bool Samochod::operator > (const Samochod &samochod) const
{
    return this->model > samochod.model;
}


//Zad.15
Samochod Samochod::operator++(int)
{
    this->liczba_kilometrow++;
    return *this;
}

Samochod Samochod::operator|=(const Samochod &samochod)
{
    this->liczba_kilometrow|=samochod.liczba_kilometrow;
    return *this;
}

Samochod Samochod::operator+(const Samochod &samochod)
{
    this->poziom_paliwa += samochod.poziom_paliwa;
    return *this;
}

Samochod Samochod::operator,(const Samochod &samochod)
{
    Samochod tmp;

    this->poziom_paliwa = samochod.poziom_paliwa;

    return *this;
}