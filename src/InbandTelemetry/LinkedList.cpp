#include "LinkedList.h"
#include <stdio.h>
#include <iostream>

using namespace std;

template <class T>
LinkedList<T>::LinkedList()
{
	head = NULL;
	tail = NULL;
	count = 0;
}

template <class T>
void LinkedList<T>::AppendNode(T val)
{
	Node<T> *node = new Node<T>();

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

template <class T>
void LinkedList<T>::Print()
{
	for (Node<T>* node = head; node != NULL; node = node->next)
	{
		cout << node->val << " ";
	}

}

template <class T>
int LinkedList<T>::GetCount()
{
	return count;
}

template <class T>
void LinkedList<T>::Dispose()
{
	for (Node<T>* node = head; node != NULL; node = node->next)
	{
		Node<T>* temp = node->next;
		if (temp != NULL)
		{
			delete temp;
		}
	}

	head = NULL;
	tail = NULL;
}

template class LinkedList<int>;

