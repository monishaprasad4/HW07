/** EdgeLength.cpp
 *  Implementation for the EdgeLength class
 *
 *  Maintains a list of edges of the same length in the graph.
 *  Used to find matching set using the Greedy Algorithm
 */

#include <iostream>
#include "EdgeLength.h"

/** Output operator for cout
 *
 *  Outputs the instance variables
 */
std::ostream& operator<<(std::ostream& os, const EdgeLength& edgeLength)
{
    os << "Length: " << edgeLength.length;

    return os;
}
