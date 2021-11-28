#include <iostream>
#include "Graph.h"

using namespace std;

Graph::Graph()
{
	numVertices = 0;
	numEdges = 0;
    vertexList = NULL;
    distanceMatrix = NULL;
    oddVertices = NULL;
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
    distanceMatrix = new int* [numVertices + 1];
    for (int i = 0; i < numVertices + 1; i++)
    {
        distanceMatrix[i] = new int[numVertices + 1];
    }

    for (int i = 1; i <= numVertices; i++)
    {
        for (int j = 1; j <= numVertices; j++)
        {

            if (i == j)
            {
                distanceMatrix[i][j] = 0;
            }
            else
            {
                distanceMatrix[i][j] = INT_MAX/2;
            }
        }
    }

    for (int i = 1; i <= numVertices; i++)
    {
        int vertex = vertexList[i].head->val;

        for (Node* node = vertexList[i].head->next; node != NULL; node = node->next)
        {
            distanceMatrix[vertex][node->val] = 1;
        }
    }

    for (int k = 1; k <= numVertices; k++)
    {
        for (int i = 1; i <= numVertices; i++)
        {
            for (int j = 1; j <= numVertices; j++)
            {
                if (distanceMatrix[i][j] > distanceMatrix[i][k] + distanceMatrix[k][j])
                {
                    distanceMatrix[i][j] = distanceMatrix[i][k] + distanceMatrix[k][j];
                }
            }
        }
    }

    /*
    cout << "\n\nFwMatrix: " << endl;

    for (int i = 1; i <= numVertices; i++)
    {
        for (int j = 1; j <= numVertices; j++)
        {
            cout << distanceMatrix[i][j] << " ";
        }

        cout << endl;
    }

    */
}

void Graph::PrintShortestPathOddVertices()
{
    if (distanceMatrix == NULL)
    {
        FindShortestPath();
    }

    cout << endl << "Results of Floyd-Warshall on O:" << endl;

    if (oddVertices == NULL)
    {
        FindOddVertices();
    }

    printf("     | ");

    for (Node* node = oddVertices->head; node != NULL; node = node->next)
    {
        printf("  %2d", node->val);
    }

    printf("\n--- -+-");
    for (int i = 0; i < oddVertices->GetCount(); i++)
    {
        printf(" ---");
    }

    printf("\n");

    for (Node* node = oddVertices->head; node != NULL; node = node->next)
    {
        int vertex = node->val;
        printf(" %2d  | ", vertex);

        for (Node* node2 = oddVertices->head; node2 != NULL; node2 = node2->next)
        {
            int distance = (node2->val == vertex) ? 0 : distanceMatrix[vertex][node2->val];
            printf("  %2d", distance);
        }

        printf("\n");
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

void Graph::FindOddVertices()
{
    if (oddVertices != NULL)
    {
        return;
    }
    
    oddVertices = new LinkedList();

    for (int i = 1; i <= numVertices; i++)
    {
        int count = vertexList[i].GetCount();
        if (count > 0 && (count - 1) % 2 == 1)
        {
            oddVertices->AppendNode(i);
        }
    }
}


void Graph::PrintOddVertices()
{
    FindOddVertices();

    cout << "The odd degree verticies in G: { O = { ";

    oddVertices->Print();

    cout << "} }" << endl;
}
