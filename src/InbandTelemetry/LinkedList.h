#pragma once
#include "Node.h"
class LinkedList
{
public:
	LinkedList();
	void Print();
	void AppendNode(int val);
	int GetCount();
	void Dispose();
	Node* Head;
	Node* Tail;

private:
	int count;
};

