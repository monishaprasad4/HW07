/** Node.h
 *  Definition of the Node class
 */

#pragma once

#include <iostream>

template <class T>
class Node
{
public:
    Node(T value)
    {
        next = NULL;
        val = value;
    }

    T val;

    Node<T>* next;

    template <class U> friend std::ostream& operator<< (std::ostream& os, const Node<U>& node);

};

