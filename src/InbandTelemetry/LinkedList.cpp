#include "LinkedList.h"
#include <stdio.h>
#include <iostream>

using namespace std;

LinkedList::LinkedList()
{
	Head = NULL;
	Tail = NULL;
	count = 0;
}

void LinkedList::AppendNode(int val)
{
	Node* node = new Node();

	node->val = val;
	node->next = NULL;

	if (Head == NULL)
	{
		Head = node;
		Tail = node;
	}

	else
	{
		Tail->next = node;
		Tail = node;
	}

	count++;
}

void LinkedList::Print()
{
	for (Node* node = Head; node != NULL; node = node->next)
	{
		cout << node->val << " ";
	}

}

int LinkedList::GetCount()
{
	return count;
}

void LinkedList::Dispose()
{
	for (Node* node = Head; node != NULL; node = node->next)
	{
		Node *temp = node->next;
		if (temp != NULL)
		{
			delete temp;
		}
	}

	Head = NULL;
	Tail = NULL;
}


