/** main.cpp
 *  Main entry point into the program
 *
 *  Creates a graph object and reads it from stdin
 *  Finds the various properties of the graph and
 *  prints them to stdout
 *
 */

#include <iostream>
#include <stdio.h>
#include "Graph.h"
#include "LinkedList.h"

/** The entry point into the program. 
 *    1. Creates the graph object with input from stdin
 *    2. Generates the various properties such as shortest path
 *       between vertices, find odd degree vertices, perfect
 *       matching, and Euler circuit
 *    3. Prints the results
 */
int main()
{
    Graph* graph = new Graph();
    
    if (!graph->ReadGraph())
    {
        return -1;
    }

    // Generate the various properties of the graph
    graph->FindShortestPathBetweenVertices();

    graph->FindOddDegreeVertices();

    graph->FindShortestPathForOddDegreeVertices();

    graph->FindPerfectMatching();

    graph->InsertVirtualEdgesIntoGraph();

    graph->FindEulerCircuit();

    // Print out the results
    graph->PrintOddVertices();

    graph->PrintShortestPathOddVertices();

    graph->PrintGreedyPerfetcMatchingVertices();

    graph->PrintEulerCircuit();

    return 0;
}
