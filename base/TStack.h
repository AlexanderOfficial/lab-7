#ifndef __STACK_H__
#define __STACK_H__

#include <iostream>

using namespace std;

const int MaxStackSize = 100;

template <class T>
class TStack
{
    T* pMem;
    int size;
    int top;
    TStack(const TStack& st) {}
    TStack& operator=(const TStack& st) {}
public:
    //конструкторы 
    TStack(int _size)
    {
        size = _size;
        top = -1;
        if ((size < 1) || (size > MaxStackSize))
            throw size;
        pMem = new T[size];
    }
    //деструктор
    ~TStack()
    {
       if (pMem != NULL)
            delete[] pMem;
        //pMem = NULL;
    }
    //методы
    bool isEmpty() const // контроль пустоты
    {
        return (top == -1);
    }
    bool isFull() const // контроль переполнения
    {
        return (top == size-1);
    }
    void push(const T& val)
    {
        if (isFull())
            throw "Error";
        pMem[++top] = val;
    }
    T Pop() // извлечь значение
    {
        if (isEmpty())
            throw "Error";
        return pMem[top--];
    }
    T Top()
    {
        if (isEmpty())
            throw (top);
        return pMem[top - 1];
    }
};

#endif
