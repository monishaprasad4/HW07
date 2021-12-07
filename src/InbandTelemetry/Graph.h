/** Graph.h
 *  Definition of the Graph class
 */

#pragma once
#include <stdio.h>
#include "LinkedList.h"
#include "EdgeLength.h"
#include "AdjacencyList.h"
#include "NodePath.h"
#include "Stack.h"

class Graph
{
public:
    Graph();
    bool ReadGraph();
    int GetNumVertices();
    int GetNumEdges();
    void Print();
    void FindOddDegreeVertices();
    void FindShortestPathBetweenVertices();
    void FindShortestPathForOddDegreeVertices();
    void FindPerfectMatching();
    void InsertVirtualEdgesIntoGraph();
    void FindEulerCircuit();
    LinkedList<Edge> FindPath(int v1, int v2);

    void PrintOddVertices();
    void PrintShortestPathOddVertices();
    void PrintGreedyPerfetcMatchingVertices();
    void PrintEulerCircuit();

    AdjacencyList* GetAdjacencyLists();
    
private:
    int numVertices;
    int numEdges;
    //LinkedList<int>* vertexList;
    AdjacencyList* adjacencyLists;
    int** distanceMatrix;
    LinkedList<int>* oddVertices;
    int** distanceMatrixOddVertices;
    LinkedList<Edge>* matching;
    LinkedList<EdgeLength>* edgeLengths;
    LinkedList<NodePath>* nodePaths;
    Stack<Edge>* stack;
    LinkedList<Edge>* eulerCircuit;

    void InsertEdge(LinkedList<Edge>* edgesList, Edge edge);
    void AddEdge(int vertex1, int vertex2, int length);
    int FindIntermediateNode(int vertex1, int vertex2);
    void MarkVerticesAsUsed(Edge edge);
};

