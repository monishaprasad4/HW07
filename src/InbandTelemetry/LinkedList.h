#pragma once
#include "Node.h"
#include <stdio.h>
#include <iostream>

using namespace std;

template <class T>
class LinkedList
{
public:
	LinkedList();
	void Print();
	void AppendNode(T val);
	int GetCount();
	void Dispose();

	Node<T> *head;
	Node<T> *tail;

private:
	int count;
};


