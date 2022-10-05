#include <iostream>
#include "Osoba.h"
#include "Student.h"
#include "Pracownik.h"
#include "FabrykaOsob.h"
#include "FabrykaStudentow.h"
#include "FabrykaPracownikow.h"

//Zadanie 5
void OsobaTest()
{
    Osoba osoba;

    osoba.setName("Jan");
    osoba.setSurname("Kowalski");
    osoba.setDateOfBirth({18,7,2000});
    osoba.setAddress({"Warszawa", "Marszalkowska", "5"});

    osoba.displayInfo();
}

void StudentTest()
{
    Student student;
    student.setName("John");
    student.setSurname("Cena");
    student.setDateOfBirth({20,20,2020});
    student.setAddress({"Pardelak", "Blotna", "4"});
    student.addMark("Matematyka", 5);
    student.addMark("Historia", 3);
    student.addMark("Matematyka", 4);
    std::cout<<student.getMark("Historia")<<std::endl;
    student.displayInfo();
}

void PracownikTest()
{
    Pracownik pracownik;
    pracownik.setName("Zdzislaw");
    pracownik.setSurname("Skrzypek");
    pracownik.setDateOfBirth({13,12,1970});
    pracownik.setAddress({"NowaWies", "Brak", "14"});

    pracownik.addSubject("Matematyka");
    pracownik.addSubject("Historia");
    pracownik.displayInfo();

    pracownik.addSubject("Matematyka");
    pracownik.addSubject("Fizyka");
    pracownik.displayInfo();

    pracownik.removeSubject("Historia");
    pracownik.displayInfo();

    pracownik.checkSubject("Fizyka") ? std::cout<<"Prowadzi"<<std::endl : std::cout<<"Nie prowadzi"<<std::endl;
    pracownik.checkSubject("Historia") ? std::cout<<"Prowadzi"<<std::endl : std::cout<<"Nie prowadzi"<<std::endl;

}

//Zadanie 8a
void foo(Osoba &os)
{
    os.displayInfo();
}

//Zadanie 8b
void bar(Osoba *os)
{
    os->displayInfo();
}

void FabrykaStudentowTest()
{
    FabrykaStudentow FabSt;
    
    Student *student_z_fabryki = FabSt.utworz();
    
    student_z_fabryki->setName("Heniek");
    student_z_fabryki->displayInfo();
    
    delete student_z_fabryki;
}

void FabrykaPracownikowTest()
{
    FabrykaPracownikow FabPr;

    Pracownik *pracownik_z_fabryki = FabPr.utworz();

    pracownik_z_fabryki->setName("Gienek");
    pracownik_z_fabryki->displayInfo();

    delete pracownik_z_fabryki;
}


int main()
{
    //Zadanie 5
    OsobaTest();
    StudentTest();
    PracownikTest();

    //Zadania 9-12
    Osoba os("Osoba", "Osobowa", {12,12,1986}, {"Osobiczno", "Osobista", "0"});
    Student st("Student", "Studencki", {11,11,1975}, {"Studentowo", "Studencka", "55"});
    Pracownik pr("Pracownik", "Pracowity", {10,10,1997}, {"Pracownia", "Pracownicza", "99"});
    
    st.addMark("Programowanie Obiektowe", 5);
    pr.addSubject("Analiza Matematyczna");


    foo(os);
    foo(st);
    foo(pr);

    bar(&os);
    bar(&st);
    bar(&pr);

    //Zadania 12-14
    //Po dodaniu specyfikatora 'virtual' do metody displayInfo() zadeklarowanie przyjmowania przez funkcję 
    //obiektu typu rodzica umożliwia przekazywanie do niej dowolnego obiektu typu który z niego dziedziczy.
    //Mimo iż parametrem funkcji foo i bar jest Osoba, metody displayInfo()
    //są odpowiednie dla przekazanego obiektu. Bez specyfikatora, wszystkie te obiekty traktowane są
    //jak obiekt typu Osoba - wywoływana jest metoda displayInfo() z klasy Osoba, nie jej przeciążone odpowiedniki
    //ze Student i Pracownik.

    std::cout<<"\n\n";


    //Zadanie 15
    Pracownik *p1 = new Pracownik;
    Osoba *o1 = static_cast<Osoba *>(p1); //poprawnie, ale castowanie nie jest potrzebne
    Pracownik *p2 = static_cast<Pracownik *>(p1); //wskaźnik o1 jest ustawiony na obiekt typu Pracownik (ten sam co p1) i dlatego ta linia działa

    Osoba *o3 = new Osoba;
    Pracownik *p3 = static_cast<Pracownik *>(o3); //vector Subjects nie jest poprawnie zaalokowany, niepoprawny cast w dół dziedziczenia

    //Zadanie 16
    Pracownik *p4 = new Pracownik;
    Osoba *o4 = dynamic_cast<Osoba *>(p4); //poprawnie, ale castowanie nie jest potrzebne
    Pracownik *p5 = dynamic_cast<Pracownik *>(o4); //wskaźnik o4 jest ustawiony na obiekt typu Pracownik (ten sam co p4) i dlatego ta linia działa

    //Zadanie 17
    Osoba *o5 = new Osoba;
    Pracownik *p6 = dynamic_cast<Pracownik *>(o5); //przy dynamic_cast poprawność castowania jest sprawdzana w czasie działania programu,
                                                   //jeśli się nie powiedzie zwracana jest wartość nullptr, co zachodzi w tym przypadku
    if(p6 == nullptr) std::cout<<"Blad rzutowania!"<<std::endl;    
    
    delete p1;
    delete o3;
    delete p4;
    delete o5;

    //Zadania 22,23 Przed dodaniem specyfikatora 'virtual' destruktor niszczył tylko pola klasy osoba,
    //pomijając klasy dziedziczące, po dodaniu najpierw wywoływany jest destruktor klasy dziedziczącej a
    //potem rodzica

    //Zadanie 27
    FabrykaStudentowTest();
    FabrykaPracownikowTest();

    //Zadania 28-32
    std::map<std::string, FabrykaOsob*> m;

    m["student"] = new FabrykaStudentow();
    m["pracownik"] = new FabrykaPracownikow();

    std::vector<Osoba*> tablicaOsob;

    bool running = true;
    std::string opcja;
    while(running)
    {
        std::cout<<"1.\"student\" - utworz nowego studenta i dodaj go do tablicy osob"<<std::endl;
        std::cout<<"2.\"pracownik\" - utworz nowego pracownika i dodaj go do tablicy osob"<<std::endl;
        std::cout<<"3.\"wyswietl\" - wyswietl informacje o wszystkich osobach dodanych do tablicy"<<std::endl;
        std::cout<<"4.\"wyjscie\" - wyjscie z programu"<<std::endl;
        std::cin>>opcja;

        if(opcja=="wyswietl")
        {
            for(int i=0; i<tablicaOsob.size(); i++)
            {
                //Zadanie 33
                //tablicaOsob jest zadeklarowana dla obiektów typu Osoba, ale przyjmuje również obiekty
                //pochodzące z klas dziedziczących i dla nich wywołuje odpowiednio przeciążoną metodę
                tablicaOsob[i]->displayInfo();
            }
        }
        else if(opcja=="wyjscie")
        {
            running = false;
        }
        else if(opcja=="student" || opcja=="pracownik")
        {
            tablicaOsob.push_back(m[opcja]->utworz());
            std::cout<<"Dodano "<<opcja<<"a\n"<<std::endl;
        }
        else
        {
            std::cout<<"Sprobuj ponownie\n"<<std::endl;
        }
        
    }
    
    return 0;
}