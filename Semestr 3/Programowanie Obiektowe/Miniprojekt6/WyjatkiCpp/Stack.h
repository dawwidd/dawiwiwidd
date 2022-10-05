#pragma once

#include <vector>
#include <iostream>


// Zadanie 2
class Stack
{
private:
    const int DEFAULT_STACK_SIZE = 8;
    int maxStackSize;
    std::vector<int> dfs;
    int top;

public:
    Stack();
    Stack(int max);
    void push(int newItem);
    int pop();

    void display();    
};