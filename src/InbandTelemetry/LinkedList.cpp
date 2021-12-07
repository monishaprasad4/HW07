/** LinkedList.cpp
 *  Implementation for the LinkedList class
 *
 *  Implements a singly linked list.  Only the functions
 *  required for the graph are impleented.  This is a 
 * template class
 */

#include <stdio.h>
#include <iostream>

#include "LinkedList.h"
#include "EdgeLength.h"
#include "AdjacentNode.h"
#include "NodePath.h"

/** Constructor
  *
  *  Initializes instance variables
  */
template <class T>
LinkedList<T>::LinkedList()
{
    head = NULL;
    tail = NULL;
    count = 0;
}

/** Appends a node at the end of the list
 *
 *  @param val Value to add to the linked list
 */
template <class T>
void LinkedList<T>::AppendNode(T val)
{
    Node<T> *node = new Node<T>(val);

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

/** Inserts a node at the head of the list
 *
 *  @param val Value to insert to the linked list
 */
template <class T>
void LinkedList<T>::InsertHead(T val)
{
    if (head == NULL)
    {
        AppendNode(val);
    }
    else
    {
        Node<T>* node = new Node<T>(val);

        node->next = head;
        head = node;

        count++;
    }
}

/** Inserts a node after the specified node
 *
 *  @param node Node after which to insert
 *  @param val Value to insert to the linked list
 */
template <class T>
void LinkedList<T>::InsertAfter(Node<T>* node, T val)
{
    Node<T>* newNode = new Node<T>(val);

    newNode->next = NULL;

    if (node == tail)
    {
        tail->next = newNode;
        tail = newNode;
    }
    else
    {
        newNode->next = node->next;
        node->next = newNode;
    }

    count++;
}

/** Removes the head of the list and returns it
 *
 *  Note: Throws an exception if list is empty
 *  @returns head.
 */
template <class T>
T LinkedList<T>::RemoveHead()
{
    if (head != NULL)
    {
        Node<T>* retVal = head;
        head = head->next;
        if (head == NULL)
        {
            tail = NULL;
            count = 0;
        }
        else
        {
            count--;
        }

        return retVal->val;
    }

    throw std::underflow_error("List is empty");
}

/** Returns number of items in the list
 *
 *  @returns Count of items
 */
template <class T>
int LinkedList<T>::GetCount()
{
    return count;
}

/** Prints the list to stdout
 *
 *  Note: The item being printed must override the
 *        << operator
 *  @param val Value to insert to the linked list
 */
template <class T>
void LinkedList<T>::Print()
{
    for (Node<T>* node = head; node != NULL; node = node->next)
    {
        std::cout << node->val;
        if (node->next != NULL)
        {
            std::cout << " ";
        }
    }
}

/** Deletes the list and frees resources
 *
 */
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
    count = 0;
}


template class LinkedList<int>;
template class LinkedList<EdgeLength>;
template class LinkedList<Edge>;
template class LinkedList<AdjacentNode>;
template class LinkedList<NodePath>;
