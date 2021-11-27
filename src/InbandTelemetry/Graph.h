#pragma once
#include <stdio.h>
#include "LinkedList.h"

class Graph
{
public:
	Graph();
	bool InitGraph(const char* fileName);
	int GetNumVertices();
	int GetNumEdges();
	void Print();
	void printOddVerticies();

private:
	int numVertices;
	int numEdges;
	LinkedList* vertexList;
};

