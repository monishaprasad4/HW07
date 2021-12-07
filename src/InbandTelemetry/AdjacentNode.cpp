/** AdjacentNode.cpp
 *  Implementation for the AdjacentNode class
 *
 *  Information for an adjacent node in the graph
 */

#include "AdjacentNode.h"

/** Constructor
 *
 *  Initializes instance variables
 */
AdjacentNode::AdjacentNode()
{
    vertex = 0;
    weight = 0;
    isVirtual = false;
    isUsed = false;
}

/** Constructor
 *
 *  Initializes instance variables
 *
 *  @param vertex The vertex of the adjacent node
 */
AdjacentNode::AdjacentNode(int vertex)
{
    this->vertex = vertex;
    weight = 0;
    isVirtual = false;
    isUsed = false;
}

/** Constructor
 *
 *  Initializes instance variables
 *
 *  @param vertex The vertex of the adjacent node
 *  @param weight Weight of edge connnecting to the vertex
 */
AdjacentNode::AdjacentNode(int vertex, int weight)
{
    this->vertex = vertex;
    this->weight = weight;
    isVirtual = false;
    isUsed = false;
}

/** Constructor
 *
 *  Initializes instance variables
 *
 *  @param vertex The vertex of the adjacent node
 *  @param weight Weight of edge connnecting to the vertex
 *  @param isVirtual Is this a virtual edge?
 */
AdjacentNode::AdjacentNode(int vertex, int weight, bool isVirtual)
{
    this->vertex = vertex;
    this->weight = weight;
    this->isVirtual = isVirtual;
    isUsed = false;
}

/** Output operator for cout
 *
 *  Outputs the instance variables
 */
std::ostream& operator<<(std::ostream& os, const AdjacentNode& adjacentNode)
{
    os << adjacentNode.vertex;

    return os;
}

