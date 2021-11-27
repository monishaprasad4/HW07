// InbandTelemetry.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include "graph.h"
#include "LinkedList.h"

using namespace std;

int main()
{
    Graph* graph = new Graph();
    const char* inputFile = "campus.txt";

    bool retValue = graph->InitGraph(inputFile);

    //graph->Print();

    graph->printOddVerticies();

    if (!retValue)
    {
        cout << "Unable to initialize graph from input file " <<
            inputFile << ". Please check if the file exists" << endl;

            return -1;
    }

    

    return 0;
}
