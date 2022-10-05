#include <string>
#include "Stack.h"
#include "StackException.h"

// Zadanie 5
void foo(Stack &s)
{
    try
    {
        for(int i=0; i<17; i++)
        {
            s.push(i);
        }
    }
    catch(StackException e)
    {
        std::cout<<"Zadanie 5: "<<e.what()<<std::endl;
    }
}

// Zadanie 6
void bar(Stack &s)
{
    try
    {
        for(int i=0; i<17; i++)
        {
            s.push(i);
        }
    }
    catch(StackException &e)
    {
        std::cout<<"Zadanie 6: "<<e.what()<<std::endl;
    }  
}



int main()
{
    Stack stos1(16);
    Stack stos2(16);

    foo(stos1);
    bar(stos2);

    // Zadania 5, 6
    // W funkcji foo() następuje zjawisko "object slicingu" - w wyniku przypisania obiektu pochodnego do instancji klasy macierzystej tracona jest część właściwa dla klasy pochodnej.
    // W funkcji bar() operacje są przeprowadzane bezpośrednio na wyjątku, który został przechwycony, wywołana jest więc metoda what() odpowiedniego potomka StackException.


    // Zadanie 7
    try
    {
        Stack stos3;
        bool running = true;
        std::string option;
        int liczba;

        while(running)
        {
            std::cout<<"Jaka operacje na stosie chcesz wykonać?"<<std::endl;
            std::cout<<"> push"<<std::endl;
            std::cout<<"> pop"<<std::endl;
            std::cout<<"> display"<<std::endl;
            std::cout<<"> quit"<<std::endl;

            std::cin>>option;

            if(option == "push")
            {
                std::cout<<"Jaką liczbę dodać do stosu?: ";
                std::cin>>liczba;
                stos3.push(liczba);
            }
            else if(option == "pop")
            {
                stos3.pop();
            }
            else if(option == "quit")
            {
                running = false;
            }
            else if(option == "display")
            {
                stos3.display();
            }
            else
            {
                std::cout<<"Bledna opcja, sprobuj ponownie."<<std::endl;
            }

            std::cout<<std::endl;
        }
    }
    catch(StackException &e)
    {
        std::cout<<e.what()<<std::endl;
    }
    catch(std::exception &e)
    {
        std::cout<<e.what()<<std::endl;
    }
    catch(...)
    {
        std::cout<<"Cos poszlo nie tak."<<std::endl;
    }

    return 0;
}