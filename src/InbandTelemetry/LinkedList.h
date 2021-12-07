/** LinkedList.h
 *  Definition of the LinkedList class
 */

#pragma once

#include "Node.h"
#include <stdio.h>
#include <iostream>

template <class T>
class LinkedList
{
public:
    LinkedList();
    void Print();
    void AppendNode(T val);
    void InsertHead(T val);
    T RemoveHead();
    void InsertAfter(Node<T> *node, T val);
    int GetCount();
    void Dispose();

    Node<T> *head;
    Node<T> *tail;

private:
    int count;
};
