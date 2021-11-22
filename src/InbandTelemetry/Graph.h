#pragma once
#include <stdio.h>

class Graph
{
public:
	Graph();
	bool InitGraph(const char* fileName);
	int GetNumVertices();
	int GetNumEdges();
	void Print();

private:
	int numVertices;
	int numEdges;
	int** vertices;
};

