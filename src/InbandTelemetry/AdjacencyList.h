/** AdjacentList.h
 *  Definition of the AdjacentList class
 */

#pragma once

#include "LinkedList.h"
#include "AdjacentNode.h"

class AdjacencyList
{
public:
    AdjacencyList();
    LinkedList<AdjacentNode> AdjacentNodes;
    int vertex;
};

