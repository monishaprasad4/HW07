#pragma once
#include "Node.h"
class LinkedList
{
public:
	LinkedList();
	void printList();
	void appendNode(int val);
	int getCount();

private:
	Node* head;
	Node* tail;
	int count;
};

