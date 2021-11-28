#pragma once
#include <stdio.h>
#include "LinkedList.h"

class Graph
{
public:
	Graph();
	bool LoadGraph(const char* fileName);
	int GetNumVertices();
	int GetNumEdges();
	void Print();
	void FindShortestPath();
	void PrintShortestPathOddVertices();
	void FindShortestPathOddVertices();
	void PrintOddVertices();
	void FindOddVertices();

private:
	int numVertices;
	int numEdges;
	LinkedList* vertexList;
	int** distanceMatrix;
	LinkedList* oddVertices;
	int** distanceMatrixOddVertices;

};

