#include "LinkedList.h"
#include <stdio.h>
#include <iostream>

using namespace std;

LinkedList::LinkedList()
{
	head = NULL;
	tail = NULL;
	count = 0;
}

void LinkedList::AppendNode(int val)
{
	Node* node = new Node();

	node->val = val;
	node->next = NULL;

	if (head == NULL)
	{
		head = node;
		tail = node;
	}

	else
	{
		tail->next = node;
		tail = node;
	}

	count++;
}

void LinkedList::Print()
{
	for (Node* node = head; node != NULL; node = node->next)
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
	for (Node* node = head; node != NULL; node = node->next)
	{
		Node *temp = node->next;
		if (temp != NULL)
		{
			delete temp;
		}
	}

	head = NULL;
	tail = NULL;
}


