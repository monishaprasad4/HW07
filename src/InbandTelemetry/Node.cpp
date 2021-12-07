/** Node.cpp
 *  Implementation for the Node class
 *
 *  This is a template class for a node in the linked list
 */

#include <iostream>
#include "Node.h"
#include "EdgeLength.h"

 /** Output operator for cout
  *
  *  Outputs the instance variables
  */
template<class T>
std::ostream& operator<<(std::ostream& os, const Node<T>& node)
{
    os << node.val;
            
    return os;
}

template class Node<int>;
template class Node<EdgeLength>;
