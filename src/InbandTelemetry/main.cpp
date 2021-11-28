// InbandTelemetry.cpp : 
// This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include "graph.h"
#include "LinkedList.h"

using namespace std;

void PrintOddVertices(LinkedList oddVertices);

int main()
{
    Graph* graph = new Graph();
    const char* inputFile = "campus.txt";

    bool retValue = graph->LoadGraph(inputFile);

    if (!retValue)
    {
        cout << "Unable to initialize graph from input file " <<
            inputFile << ". Please check if the file exists" << endl;

        return -1;
    }

    graph->PrintOddVertices();

    graph->PrintShortestPathOddVertices();

    return 0;
}


