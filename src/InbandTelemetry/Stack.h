/** Stack.h
 *  Definition of the Stack class
 */

#pragma once

#include <iostream>
#include "LinkedList.h"

template <class T>
class Stack
{
public:
    void Print();
    void Push(T val);
    T Pop();
    bool IsEmpty();
    int GetCount();

private:
    LinkedList<T> items;
};
