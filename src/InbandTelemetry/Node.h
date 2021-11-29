#pragma once

template <class T>
class Node
{
public:
	Node();
	T val;
	Node<T>* next;
};

