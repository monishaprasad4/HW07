#include "LinkedList.h"
#include <stdio.h>
#include <iostream>
using namespace std;

LinkedList::LinkedList()
{
	this->head = NULL;
	this->tail = NULL;
	count = 0;
}

void LinkedList::appendNode(int val)
{
	Node* temp = new Node();
	temp->val = val;
	temp->next = NULL;

	if (head == NULL)
	{
		head = temp;
		tail = temp;
	}

	else
	{
		tail->next = temp;
		tail = temp;
	}

	count++;
	
}

void LinkedList::printList()
{
	for (Node* node = head; node != NULL; node = node->next)
	{
		cout << node->val << " ";
	}

}

int LinkedList::getCount()
{
	return count;
}




