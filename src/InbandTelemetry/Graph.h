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
	LinkedList GetOddVertices();

private:
	int numVertices;
	int numEdges;
	LinkedList* vertexList;
	int** fwMatrix;
};

