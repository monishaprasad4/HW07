#include <iostream>
#include "Graph.h"

using namespace std;

Graph::Graph()
{
	numVertices = 0;
	numEdges = 0;
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
       // cout << num1 << " " << num2 << endl;

        if (linenumber == 1)
        {
            numVertices = num1;
            numEdges = num2;
            vertexList = new LinkedList[numVertices + 1];
            linenumber++;
            continue;
        }

        vertexList[num1].appendNode(num2);
        vertexList[num2].appendNode(num1);



        linenumber++;
        if (linenumber > numEdges + 1)
        {
            break;
        }


        
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
    for (int i = 1; i <= numVertices; i++)
    {
        cout << i << " ";
        vertexList[i].printList();
        cout << endl;
    }


}

void Graph::printOddVerticies()
{
    cout << "The odd degree verticies in G: { O = { ";
    for (int i = 1; i <= numVertices; i++)
    {
        int count = vertexList[i].getCount();
        if (count % 2 == 1)
        {
            cout << i << " ";
        }
    }
    cout << "} }" << endl;
}