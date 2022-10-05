#pragma once

#include "FabrykaOsob.h"
#include "Pracownik.h"

//Zadanie 26
class FabrykaPracownikow : public FabrykaOsob
{
public:
    Pracownik* utworz();
    
};