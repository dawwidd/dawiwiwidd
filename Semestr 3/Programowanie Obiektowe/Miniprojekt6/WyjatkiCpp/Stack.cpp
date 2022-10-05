#include "Stack.h"
#include "StackException.h"


Stack::Stack()
{
    maxStackSize = DEFAULT_STACK_SIZE;
}

Stack::Stack(int max)
{
    maxStackSize = max;
}


void Stack::push(int newItem)
{
    if(dfs.size()+1 > maxStackSize) throw StackFullException();
    else dfs.push_back(newItem);

}

int Stack::pop()
{
    if(dfs.empty()) throw StackEmptyException();
    else
    {
        top = dfs.back();
        dfs.pop_back();
        return top;
    }
}


void Stack::display()
{
    for(int i=0; i<dfs.size(); i++)
    {
        std::cout<<dfs[i]<<" ";
    }
    std::cout<<std::endl;
}