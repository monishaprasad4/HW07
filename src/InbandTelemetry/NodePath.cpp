/** NodePath.cpp
 *  Implementation for the NodePath class
 *
 *  Represents the shortest path from a source node to a target node
 *  through an intermediate node in between.
 */

#include "NodePath.h"

 /** Constructor
  *
  *  Initializes instance variables
  */
NodePath::NodePath()
{
    vertex1 = 0;
    vertex2 = 0;
    intermediateVertex = 0;
}

/** Constructor
 *
 *  Initializes instance variables
 *
 *  @param v1 The start vertex 
 *  @param v2 The end vertex
 *  @param intermediate The intermediate node
 */
NodePath::NodePath(int v1, int v2, int intermediate)
{
    vertex1 = v1;
    vertex2 = v2;
    intermediateVertex = intermediate;
}

/** Output operator for cout
 *
 *  Outputs the instance variables
 */
std::ostream& operator<<(std::ostream& os, const NodePath& nodePath)
{
    os << "(" << nodePath.vertex1 << "," << nodePath.vertex2 << ", " << nodePath.intermediateVertex << ")";

    return os;
}
