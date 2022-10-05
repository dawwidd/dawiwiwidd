#pragma once

#include <exception>
#include <string>


//Zadanie 3
class StackException : public std::exception
{
public:
    StackException(){}
    
    // Użycie modyfikatora override pozwala na nadpisanie funkcji z klasy macierzystej.
    // Podobnie jak w Javie, adnotacja ta jest informacją dla programisty i kompilatora.
    // W razie błędu programisty przy nadpisywaniu funkcji, kompilator zwraca błąd.
    // "noexcept" natomiast zapewnia iż funkcja what() sama nie zwróci nigdy żadnego wyjątku.
    virtual const char* what() const noexcept override;
};


class StackFullException : public StackException
{
private:
    int element = 0;
    int maxStackSize = 0;
    std::string message;

public:
    StackFullException(){}
    StackFullException(std::string p, int e, int s);

    virtual const char* what() const noexcept override;
};

class StackEmptyException : public StackException
{
private:
    std::string message;

public:
    StackEmptyException(){}
    StackEmptyException(std::string p);

    virtual const char* what() const noexcept override;
};


