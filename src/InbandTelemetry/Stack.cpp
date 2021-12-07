/** Stack.cpp
 *  Implementation for the Stack class
 *
 *  Implements a stack with Push, Pop and other 
 *  stack operations. This is a template class which
 *  internally uses the LinkedList class to store
 *  the items in the stack
 */

#include "Stack.h"
#include "Edge.h"

/** Push operation
 *
 *  Pushes the value to the top of the stack
 *
 *  @param val Value to push
 */
template <class T>
void Stack<T>::Push(T val)
{
    items.InsertHead(val);
}

/** Pop operation
 *
 *  Pops the value from top of stack and returns it
 *  Note:  if the stack is empty, throws a Stack underflow
 *  exception
 *
 *  @return Value popped
 */
template <class T>
T Stack<T>::Pop()
{
    return items.RemoveHead();
}

/** Checks if stack is empty
 *
 *  @return true if it is
 */
template <class T>
bool Stack<T>::IsEmpty()
{
    return items.GetCount() <= 0;
}

/** Returns count
 *
 *  The number of items in the stack
 * 
 *  @return count
 */

template <class T>
int Stack<T>::GetCount()
{
    return items.GetCount();
}

/** Prints the stack
 *
 * Prints to stdout
 */

template <class T>
void Stack<T>::Print()
{
    std::cout << "Stack contents: ";
    items.Print();
}


template class Stack<Edge>;
