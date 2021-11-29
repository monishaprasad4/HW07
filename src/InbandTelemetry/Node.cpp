#include "Node.h"
#include <cstddef>

template <class T>
Node<T>::Node()
{
	val = 0;
	next = NULL;
}

template class Node<int>;