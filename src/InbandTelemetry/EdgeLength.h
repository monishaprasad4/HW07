/** EdgeLength.h
 *  Definition of the EdgeLength class
 */

#pragma once

#include <iostream>
#include "LinkedList.h"
#include "Edge.h"

class EdgeLength
{
public:

    LinkedList<Edge>* edgesList;

    int length;
    friend std::ostream& operator<< (std::ostream& os, const EdgeLength& edgeLength);
};

