#pragma once

#include "FabrykaOsob.h"
#include "Student.h"

//Zadanie 25
class FabrykaStudentow : public FabrykaOsob
{
public:
    Student* utworz();
};