#include "Samochod.hpp"
#include <vector>
#include <algorithm>
#include <set>
#include <type_traits>

//Zad.12
struct cmp
{
    bool operator () (Samochod a, Samochod b) const
    {
        return a.getPojemnoscBaku() < b.getPojemnoscBaku();
    }
};

//Zad.14
bool cmpb(Samochod a, Samochod b)
{
    return a.getPojemnoscBaku() < b.getPojemnoscBaku();
}


int main()
{
    //Zad.5/6
    Samochod s1(123, "Audi");
    Samochod s2(0, "BMW");
    Samochod s3(200, "");

    (s1)  ? std::cout<<"s1 true"<<std::endl : std::cout<<"s1 false"<<std::endl;
    !(s1) ? std::cout<<"s1 true"<<std::endl : std::cout<<"s1 false"<<std::endl;
    (s2)  ? std::cout<<"s2 true"<<std::endl : std::cout<<"s2 false"<<std::endl;
    !(s2) ? std::cout<<"s2 true"<<std::endl : std::cout<<"s2 false"<<std::endl;
    (s3)  ? std::cout<<"s3 true"<<std::endl : std::cout<<"s3 false"<<std::endl;
    !(s3) ? std::cout<<"s3 true"<<std::endl : std::cout<<"s3 false"<<std::endl;
    
    //Zad.9 Sprawdzenie dzialania
    (s3<s2) ? std::cout<<"true\n"<<std::endl : std::cout<<"false\n"<<std::endl;
    

    //Zad.9-11
    std::vector<Samochod> v;
    v.push_back(s1);
    v.push_back(s2);
    v.push_back(s3);

    std::sort(v.begin(), v.end());

    for(auto it=v.begin(); it!=v.end(); ++it)
    {
        std::cout<<"vector "<<*it;
    }
    std::cout<<std::endl;

    //Zad.13
    std::set<Samochod, cmp> s;
    
    s.insert(s1);
    s.insert(s2);
    s.insert(s3);

    for(auto it=s.begin(); it!=s.end(); ++it)
    {
        std::cout<<"cmp "<<*it;
    }
    std::cout<<std::endl;

    //Zad.14
    auto cmpa = [](Samochod a, Samochod b){return a.getPojemnoscBaku()<b.getPojemnoscBaku();};

    std::set<Samochod, decltype(cmpa)> sa(cmpa);

    sa.insert(s1);
    sa.insert(s2);
    sa.insert(s3);

    for(auto it=sa.begin(); it!=sa.end(); ++it)
    {
        std::cout<<"cmpa "<<*it;
    }
    std::cout<<std::endl;
    
    
    using Cmp = std::integral_constant<decltype(&cmpb), &cmpb>;

    std::set<Samochod, Cmp> sb;    

    sb.insert(s1);
    sb.insert(s2);
    sb.insert(s3);

    for(auto it=sb.begin(); it!=sb.end(); ++it)
    {
        std::cout<<"cmpb "<<*it;
    }


    //Zad.15 Sprawdzanie działania przeciążonych operatorów
    std::cout<<std::endl<<"Operator++"<<std::endl;
    std::cout<<"Liczba kilometrow s1: "<<s1.getLiczbaKilometrow()<<std::endl;
    s1++;
    std::cout<<"Liczba kilometrow s1++: "<<s1.getLiczbaKilometrow()<<std::endl;

    std::cout<<std::endl<<"Operator|="<<std::endl;
    s1.setLiczbaKilometrow(50);
    s2.setLiczbaKilometrow(60);

    std::cout<<"s1: "<<s1.getLiczbaKilometrow()<<" "<<"s2: "<<s2.getLiczbaKilometrow()<<std::endl;
    s1|=s2;
    std::cout<<"s1|=s2: "<<s1.getLiczbaKilometrow()<<" "<<"s2: "<<s2.getLiczbaKilometrow()<<std::endl;

    std::cout<<std::endl<<"Operator,"<<std::endl;
    s1.setPoziomPaliwa(1);
    s2.setPoziomPaliwa(2);
    s3.setPoziomPaliwa(3);

    printf("Poz paliwa przed: s1:%g, s2:%g, s3: %g\n", s1.getPoziomPaliwa(),s2.getPoziomPaliwa(),s3.getPoziomPaliwa());
    s1 = (s1,s2,s3);
    printf("Poz paliwa po s1=(s1,s2,s3): s1:%g, s2:%g, s3: %g\n\n", s1.getPoziomPaliwa(),s2.getPoziomPaliwa(),s3.getPoziomPaliwa());

    //Zad.4 Demonstracja wymyslonych metod
    s1.tankuj(2000);

    int start = s1.getLiczbaKilometrow();
    while(s1.getPoziomPaliwa()>0.0)
    {
        s1.jedz();
    }
    int finish = s1.getLiczbaKilometrow();

    std::cout<<"s1 przejechal "<<finish-start<<" kilometrow"<<std::endl;

    return 0;
}