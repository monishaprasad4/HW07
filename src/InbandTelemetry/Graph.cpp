#include <iostream>
#include "Graph.h"

using namespace std;

Graph::Graph()
{
	numVertices = 0;
	numEdges = 0;
    vertexList = NULL;
}


bool Graph::LoadGraph(const char* fileName)
{
    FILE* fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        cout << "Error opening input file" << endl;
        return false;
    }

    char line[256];
    int linenumber = 1;
    
    if (vertexList != NULL)
    {
        vertexList->Dispose();
        vertexList = NULL;
    }

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        int num1;
        int num2;

        int fields = sscanf(line, "%d%d", &num1, &num2);
        if (fields < 2)
        {
            continue;
        }

        if (linenumber == 1)
        {
            numVertices = num1;
            numEdges = num2;
            vertexList = new LinkedList[numVertices + 1];

            for (int i = 1; i <= numVertices; i++)
            {
                vertexList[i].AppendNode(i);
            }

            linenumber++;
            continue;
        }

        vertexList[num1].AppendNode(num2);
        vertexList[num2].AppendNode(num1);

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
	
void Graph::FindShortestPath()
{
    fwMatrix = new int* [numVertices + 1];
    for (int i = 0; i < numVertices + 1; i++)
    {
        fwMatrix[i] = new int[numVertices + 1];
    }

    for (int i = 1; i <= numVertices; i++)
    {
        for (int j = 1; j <= numVertices; j++)
        {

            if (i == j)
            {
                fwMatrix[i][j] = 0;
            }
            else
            {
                fwMatrix[i][j] = INT_MAX/2;
            }
        }
    }

    for (int i = 1; i <= numVertices; i++)
    {
        int vertex = vertexList[i].Head->val;

        for (Node* node = vertexList[i].Head->next; node != NULL; node = node->next)
        {
            fwMatrix[vertex][node->val] = 1;
        }
    }



    /*
    for (int k = 1; k <= numVertices; k++)
    {
        for (int i = 1; i <= numVertices; i++)
        {
            cout << fwMatrix[k][i] << " ";
        }


        cout << endl;
    }
    */

    for (int k = 1; k <= numVertices; k++)
    {
        for (int i = 1; i <= numVertices; i++)
        {
            for (int j = 1; j <= numVertices; j++)
            {
                if (fwMatrix[i][j] > fwMatrix[i][k] + fwMatrix[k][j])
                {
                    fwMatrix[i][j] = fwMatrix[i][k] + fwMatrix[k][j];
                }
            }
        }
    }

    cout << "\n\nFwMatrix: " << endl;

    for (int i = 1; i <= numVertices; i++)
    {
        for (int j = 1; j <= numVertices; j++)
        {
            cout << fwMatrix[i][j] << " ";
        }

        cout << endl;
    }


}

void Graph::Print()
{
    for (int i = 1; i <= numVertices; i++)
    {
        vertexList[i].Print();
        cout << endl;
    }

    
}

LinkedList Graph::GetOddVertices()
{
    LinkedList list;

    for (int i = 1; i <= numVertices; i++)
    {
        int count = vertexList[i].GetCount();
        if (count > 0 && (count - 1) % 2 == 1)
        {
            list.AppendNode(i);
        }
    }

    return list;
}
