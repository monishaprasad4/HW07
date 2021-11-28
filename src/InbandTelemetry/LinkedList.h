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

	Node* head;
	Node* tail;

private:
	int count;
};

