#include <iostream>
#include "Graph.h"

using namespace std;

Graph::Graph()
{
	numVertices = 0;
	numEdges = 0;
    vertices = NULL;
}


bool Graph::InitGraph(const char* fileName)
{
    FILE* fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        cout << "Error opening input file" << endl;
        return false;
    }

    char line[100];
    int linenumber = 1;
    
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        int num1;
        int num2;

        sscanf(line, "%d%d", &num1, &num2);

        if (linenumber == 1)
        {
            numVertices = num1;
            numEdges = num2;

            vertices = new int* [numVertices+1];

            for (int row = 0; row <= numVertices; row++)
            {
                vertices[row] = new int[numVertices+1];

                for (int col = 0; col <= numVertices; col++)
                {
                    vertices[row][col] = 0;
                }
            }

            linenumber++;
            continue;
        }

        linenumber++;
        if (linenumber == numEdges + 1)
        {
            break;
        }


        int* row = vertices[num1];
        row[num2] = 1;

        row = vertices[num2];
        row[num1] = 1;
    }

    fclose(fp);

    return true;
}

int Graph::GetNumVertices()
{
    return numVertices;
}

int Graph::GetNumEdges()
{
	return numEdges;
}
	
void Graph::Print()
{
    for (int row = 1; row <= numVertices; row++)
    {
        for (int col = 1; col <= numVertices; col++)
        {
            cout << vertices[row][col] << " ";
        }

        cout << endl;
    }


}