/** Edge.cpp
 *  Implementation for the Edge class
 *
 *  Encapsulates information for an edge in the graph
 *  including the vertices, weight and whether this is 
 *  a virtual edge or not
 */

#include "Edge.h"

 /** Constructor
  *
  *  Initializes instance variables
  */
Edge::Edge()
{
    vertex1 = 0;
    vertex2 = 0;
    weight = 0;
    isVirtual = false;
}

/** Constructor
 *
 *  Initializes instance variables
 * 
 *  @param v1 The first vertex in the edge
 *  @param v2 The second vertex in the edge
 */
Edge::Edge(int v1, int v2)
{
    vertex1 = v1;
    vertex2 = v2;
    this->weight = 1;
    isVirtual = false;
}

/** Constructor
 *
 *  Initializes instance variables
 *
 *  @param v1 The first vertex in the edge
 *  @param v2 The second vertex in the edge
 *  @param weight Weight of the edge
 */
Edge::Edge(int v1, int v2, int weight)
{
    vertex1 = v1;
    vertex2 = v2;
    this->weight = weight;
    isVirtual = false;
}

/** Output operator for cout
 *
 *  Outputs the instance variables
 */
std::ostream& operator<<(std::ostream& os, const Edge& edge)
{
    os << "(" << edge.vertex1 << "," << edge.vertex2 << ")";

    return os;
}
