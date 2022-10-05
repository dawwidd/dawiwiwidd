#include "StackException.h"



const char* StackException::what() const noexcept
{
    return "Bledna operacja na stosie!\n";
}



StackFullException::StackFullException(std::string p, int e, int s)
{
    element=e;
    message=p;
    maxStackSize=s;
}

const char* StackFullException::what() const noexcept
{
    return "Przekroczono rozmiar stosu!\n";
}



StackEmptyException::StackEmptyException(std::string p)
{
    message=p;
}

const char* StackEmptyException::what() const noexcept
{
    return "Stos jest pusty!\n";
}