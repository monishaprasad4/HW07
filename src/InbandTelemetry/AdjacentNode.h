/** AdjacentNode.h
 *  Definition of the AdjacentNode class
 */

#pragma once
#include<iostream>

class AdjacentNode
{
public:
    AdjacentNode();
    AdjacentNode(int vertex);
    AdjacentNode(int vertex, int weight);
    AdjacentNode(int vertex, int weight, bool isVirtual);

    int vertex;
    int weight;
    bool isVirtual;
    bool isUsed;

    friend std::ostream& operator<< (std::ostream& os, const AdjacentNode& edge);
};

