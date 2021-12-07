/** Edge.h
 *  Definition of the Edge class
 */

#pragma once

#include<iostream>

class Edge
{
public:
    int vertex1;
    int vertex2;
    int weight;
    bool isVirtual;

    Edge();
    Edge(int vertex1, int vertex2);
    Edge(int vertex1, int vertex2, int weight);

    bool operator<(const Edge& other) const
    {
        if (vertex1 < other.vertex1)
        {
            return true;
        }
        else if (vertex1 == other.vertex1 && vertex2 < other.vertex2)
        {
            return true;
        }

        return false;
    }

    friend std::ostream& operator<< (std::ostream& os, const Edge& edge);
};

