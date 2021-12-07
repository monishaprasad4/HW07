/** Graph.cpp
 *  Implementation for the Graph class
 *
 *  The main Graph class that contains methods for:
 *    Reading the graph
 *    Creating adjacency lists
 *    Finding the shortest paths between the vertices
 *    Inserting virtual edges
 *    Finding matching set using the Greedy Algorithm
 *    Finding the Euler circuit
 *    Printing the results of the algorithms
 */

#include <iostream>
#include <climits>
#include "Graph.h"

/** Constructor
 *
 *  Initializes instance variables
 */
Graph::Graph()
{
    numVertices = 0;
    numEdges = 0;
    adjacencyLists = NULL;
    distanceMatrix = NULL;
    distanceMatrixOddVertices = NULL;
    oddVertices = NULL;
    edgeLengths = NULL;
    matching = NULL;
    nodePaths = NULL;
    eulerCircuit = NULL;
    stack = NULL;
}

/** Reads graph vertices from stdin
 * 
 * The format of the input file containing the graph is as follows. 
 * The first line in the file contains two positive integers:
 *   n m
 * where n = |V| is the number of vertices in G, and m = |E|
 * is the number of edges in G.
 * Each of the next m lines has two space separated fields of the form:
 *   u v
 * where u and v are two integers in the interval [1,n] denoting the 
 * vertices that are the endpoints of the edge.
 * Because the graph is undirected, each line in the file represents 
 * an edge connecting vertex u and vertex v;
 * The weight of each edge is equal to one.
 * 
 * @returns true on success, false on error
 */
bool Graph::ReadGraph()
{
    bool returnValue = true;
    char line[512];
    int lineNumber = 1;
    
    while (fgets(line, sizeof(line), stdin) != NULL)
    {
        int num1;
        int num2;

        int fields = sscanf(line, "%d%d", &num1, &num2);
        if (fields < 2)
        {
            std::cout << std::endl << "Invalid entry found in line number " << lineNumber << std::endl;
            return false;
        }

        if (lineNumber == 1)
        {
            numVertices = num1;
            numEdges = num2;

            // allocate the adjacency list for each vertex
            // in the graph

            adjacencyLists = new AdjacencyList[numVertices + 1];

            for (int i = 1; i <= numVertices; i++)
            {
                adjacencyLists[i].vertex = i;
            }

            lineNumber++;
            continue;
        }

        // add the nodes to the adjacency lists of the two vertices
        adjacencyLists[num1].AdjacentNodes.AppendNode(AdjacentNode(num2));
        adjacencyLists[num2].AdjacentNodes.AppendNode(AdjacentNode(num1));
        
        lineNumber++;
        if (lineNumber > numEdges + 1)
        {
            break;
        }
    }

    if (numEdges <= 0)
    {
        std::cout << std::endl << "Invalid number of edges specified: " << numEdges << std::endl;
        returnValue = false;
    }
    else if (lineNumber <= numEdges + 1)
    {
        std::cout << std::endl << "Input error. Specified " << numEdges << 
                                " edges, found only " << (lineNumber - 2) << " edge(s)" << std::endl;
        returnValue = false;
    }

    return returnValue;
}

/** Creates list of odd degree vertices
 *
 * These are vertices that are directly connected to odd
 * number of other vertices
 * 
 * The vertices are stored in the oddVertices linked list
 */
void Graph::FindOddDegreeVertices()
{
    if (oddVertices != NULL)
    {
        return;
    }

    oddVertices = new LinkedList<int>();

    for (int i = 1; i <= numVertices; i++)
    {
        int count = adjacencyLists[i].AdjacentNodes.GetCount();
        if (count > 0 && (count) % 2 == 1)
        {
            oddVertices->AppendNode(i);
        }
    }
}

/** Uses Floyd-Warshall algorithm to
 *  find shortest path between all the vertices in the graph
 *  
 *  The distances are stored in a 2-D matrix distanceMatrix
 *  where distanceMatrix[u,v] = the distance between the vertices
 *  u and v
 * 
 *  Also creates a list of node paths that contains the start
 *  vertex, the end vertex and an intermediate vertex that is a 
 *  part of the shortest path.
 */
void Graph::FindShortestPathBetweenVertices()
{
    nodePaths = new LinkedList<NodePath>();

    // allocate the 2-D matrix
    distanceMatrix = new int* [numVertices + 1];
    for (int i = 0; i < numVertices + 1; i++)
    {
        distanceMatrix[i] = new int[numVertices + 1];
    }

    // initialize the matrix. All diagonal elements
    // 0 and others are INT_MAX/2
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

    // distances to directly connected nodes are all 1
    for (int i = 1; i <= numVertices; i++)
    {
        int vertex = adjacencyLists[i].vertex;

        for (Node<AdjacentNode>* node = adjacencyLists[i].AdjacentNodes.head; node != NULL; node = node->next)
        {
            distanceMatrix[vertex][node->val.vertex] = 1;
        }
    }

    // these loops are the core of the Floyd-Warshall algorithm
    for (int k = 1; k <= numVertices; k++)
    {
        for (int i = 1; i <= numVertices; i++)
        {
            for (int j = 1; j <= numVertices; j++)
            {
                if (distanceMatrix[i][j] > distanceMatrix[i][k] + distanceMatrix[k][j])
                {
                    distanceMatrix[i][j] = distanceMatrix[i][k] + distanceMatrix[k][j];
                    nodePaths->AppendNode(NodePath(i, j, k));
                }
            }
        }
    }
}

/** Creates a 2-D matrix of shortest distances of 
 *   odd vertices in the graph 
 * 
 *  Uses the distanceMatrix and stores the shortest distance
 *  between odd vertices in the graph.  The distances are stored
 *  in the distanceMatrixOddVertices 2-D array
 */
void Graph::FindShortestPathForOddDegreeVertices()
{
    if (distanceMatrixOddVertices != NULL)
    {
        return;
    }

    FindOddDegreeVertices();

    int numOddVertices = oddVertices->GetCount();

    // allocate the matrix to store the data
    distanceMatrixOddVertices = new int* [numOddVertices + 1];
    for (int i = 0; i < numOddVertices + 1; i++)
    {
        distanceMatrixOddVertices[i] = new int[numOddVertices + 1];
    }

    int index = 1;
    for (Node<int>* node = oddVertices->head; node != NULL; node = node->next, index++)
    {
        distanceMatrixOddVertices[0][index] = node->val;
        distanceMatrixOddVertices[index][0] = node->val;
    }
    
    // now populate the 2-D array with the distances
    int row = 1;
    for (Node<int> *node = oddVertices->head; node != NULL; node = node->next, row++)
    {
        int vertex = node->val;
        int col = 1;
        for (Node<int>* node2 = oddVertices->head; node2 != NULL; node2 = node2->next, col++)
        {
            int distance = (node2->val == vertex) ? 0 : distanceMatrix[vertex][node2->val];
            distanceMatrixOddVertices[row][col] = distance;
        }
    }
}

/** Finds matching set of edges using Greedy Algorithm
 *
 *  For an undirected graph, a matching is a set of edges such 
 *  that no two edges in the set are incident on the same vertex. 
 *  A perfect matching is a matching in which every vertex is matched. 
 * 
 *  Finds matching set only for odd vertices and stores the list of 
 *  matching edges in the "matching" array
 */
void Graph::FindPerfectMatching()
{
    matching = new LinkedList<Edge>();

    if (distanceMatrixOddVertices == NULL)
    {
        return;
    }

    // create lists of edges of different lengths
    // Edges of lengths 1, edges of length 2 etc
    int numOddVertices = oddVertices->GetCount();
    for (int row = 1; row <= numOddVertices; row++)
    {
        for (int col = row; col <= numOddVertices; col++)
        {
            if (row == col)
            {
                continue;
            }

            AddEdge(distanceMatrixOddVertices[row][0], distanceMatrixOddVertices[0][col], distanceMatrixOddVertices[row][col]);
        }
    }

    if (edgeLengths == NULL)
    {
        return;
    }

    if (edgeLengths->GetCount() == 0)
    {
        return;
    }

    // now create the matching set by going through the lists of 
    // various lengths and pick edges that are not incident
    // on the same vertex
    matching->AppendNode(edgeLengths->head->val.edgesList->head->val);

    for (Node<EdgeLength>* edgeLengthNode = edgeLengths->head; edgeLengthNode != NULL; edgeLengthNode = edgeLengthNode->next)
    {
        for (Node<Edge>* edgeNode = edgeLengthNode->val.edgesList->head; edgeNode != NULL; edgeNode = edgeNode->next)
        {
            bool found = false;
            for (Node<Edge>* matchingNode = matching->head; matchingNode != NULL; matchingNode = matchingNode->next)
            {
                if (edgeNode->val.vertex1 == matchingNode->val.vertex1 ||
                    edgeNode->val.vertex1 == matchingNode->val.vertex2 ||
                    edgeNode->val.vertex2 == matchingNode->val.vertex1 ||
                    edgeNode->val.vertex2 == matchingNode->val.vertex2)
                {
                    found = true;
                    break;
                }

            }

            if (!found)
            {
                matching->AppendNode(edgeNode->val);
            }
        }
    }
}

/** For each edge in the matching set, insert
*   a virtual edge in the graph
* For each edge in the greedy perfect matching, i.e., 
* for each e = (u, v) in M, insert a virtual edge into G
* with weight w equal to the length of the shortest path between 
* u and v in G. 
* Virtual edges are inserted into the adjacency lists for (u; v) 
* after the original edge in G
*/
void Graph::InsertVirtualEdgesIntoGraph()
{
    for (Node<Edge>* node = matching->head; node != NULL; node = node->next)
    {
        Node<AdjacentNode>* adjacentNode = adjacencyLists[node->val.vertex1].AdjacentNodes.head;

        // update the adjacency list for vertex1
        for (Node<AdjacentNode>* prevNode = adjacentNode; adjacentNode != NULL; adjacentNode = adjacentNode->next)
        {
            if (node->val.vertex2 < adjacentNode->val.vertex)
            {
                if (adjacentNode == adjacencyLists[node->val.vertex1].AdjacentNodes.head)
                {
                    adjacencyLists[node->val.vertex1].AdjacentNodes.InsertHead(AdjacentNode(node->val.vertex2, node->val.weight, true));
                }
                else
                {
                    adjacencyLists[node->val.vertex1].AdjacentNodes.InsertAfter(prevNode, 
                                        AdjacentNode(node->val.vertex2, node->val.weight, true));
                }

                break;
            }

            prevNode = adjacentNode;
        }

        if (adjacentNode == NULL)
        {
            adjacencyLists[node->val.vertex1].AdjacentNodes.AppendNode(AdjacentNode(node->val.vertex2, node->val.weight, true));
        }

        adjacentNode = adjacencyLists[node->val.vertex2].AdjacentNodes.head;

        // update the adjacency list for vertex2
        for (Node<AdjacentNode>* prevNode = adjacentNode; adjacentNode != NULL; adjacentNode = adjacentNode->next)
        {
            if (node->val.vertex1 < adjacentNode->val.vertex)
            {
                if (adjacentNode == adjacencyLists[node->val.vertex2].AdjacentNodes.head)
                {
                    adjacencyLists[node->val.vertex2].AdjacentNodes.InsertHead(AdjacentNode(node->val.vertex1, node->val.weight, true));
                }
                else
                {
                    adjacencyLists[node->val.vertex2].AdjacentNodes.InsertAfter(prevNode, 
                                        AdjacentNode(node->val.vertex1, node->val.weight, true));
                }

                break;
            }

            prevNode = adjacentNode;
        }

        if (adjacentNode == NULL)
        {
            adjacencyLists[node->val.vertex2].AdjacentNodes.AppendNode(AdjacentNode(node->val.vertex1, node->val.weight, true));
        }
    }
}

/** Finds the euler circuit and stores the edges
* in the eulerCircuit linked list
* 
* The algorithm is as follows
*   1. Start with an empty stack and an empty circuit. 
*      Start at vertex 1, i.e., let u = 1 be the current vertex.
*   2. If the current vertex has no more edges incident with it, 
*      pop the last edge (u; v) on the stack, append (v; u) to the 
*      circuit, and set u to the current vertex. Otherwise, i.e.,
*      the current u vertex has edges incident with it. 
*      Select the next  edge incident with u, say (u, v), and push
*      it onto the stack. Remove (u; v) from G (or mark it as used), 
*      and let u = v. 
*      To guarantee the output format, it is crucial that edges be selected in 
*      lexicographic order, always selecting original edges before 
*      virtual edges. When a virtual edge is used, recover the shortest 
*      path in G corresponding to the virtual edge.
*   3. Repeat step 2 until the current vertex has no more edges incident 
*      with it and the stack is empty
*/
void Graph::FindEulerCircuit()
{
    stack = new Stack<Edge>();

    eulerCircuit = new LinkedList<Edge>();

    int u = 1;

    bool done = false;

    while (!done)
    {
        Node<AdjacentNode>* node;

        // find the next unused node
        for (node = adjacencyLists[u].AdjacentNodes.head; node != NULL && node->val.isUsed; node = node->next)
            ;

        // all nodes are used
        if (node == NULL)
        {
            // we are done. quit the loop
            if (stack->IsEmpty())
            {
                done = true;
                continue;
            }

            // pop the stack
            Edge edge = stack->Pop();


            if (edge.isVirtual)
            {
                // add shortest path nodes to the euler circuit
                LinkedList<Edge> path = FindPath(edge.vertex2, edge.vertex1);

                for (Node <Edge>* node = path.head; node != NULL; node = node->next)
                {
                    eulerCircuit->AppendNode(Edge(node->val.vertex1, node->val.vertex2));
                }
            }
            else
            {
                // just add the edge
                eulerCircuit->AppendNode(Edge(edge.vertex2, edge.vertex1));
            }

            u = edge.vertex1;
            continue;
        }

        // Push the edge onto the stack
        Edge edge = Edge(u, node->val.vertex);
        edge.isVirtual = node->val.isVirtual;

        MarkVerticesAsUsed(edge);

        stack->Push(edge);

        u = node->val.vertex;
    }
}

/** Returns a list of nodes that appear
*   along the shortest path from vertex1 to vertex2
* 
* @param1 vertex1  The first vertex
* @param2 vertex2  The second vertex
* 
* @returns a list of vertices from vertex1 to vertex2
*/
LinkedList<Edge> Graph::FindPath(int vertex1, int vertex2)
{
    LinkedList<Edge> list;

    int v1 = vertex1;
    int v2 = vertex2;

    while (1)
    {
        int intermediateNode = FindIntermediateNode(v1, v2);
        if (intermediateNode == 0)
        {
            list.InsertHead(Edge(v1, v2));
            return list;
        }
        else
        {
            list.InsertHead(Edge(intermediateNode, v2));
            v2 = intermediateNode;
        }
    }
}

/** Finds an intermediate node along the shortest
*  path between vertex1 and vertex2
*  along the shortest path from vertex1 to vertex2
*
* @param1 vertex1  The first vertex
* @param2 vertex2  The second vertex
*
* @returns the intermediate vertex
*/
int Graph::FindIntermediateNode(int vertex1, int vertex2)
{
    // check if vertex2 is directly connected to vertex1 
    for (Node<AdjacentNode>* node = adjacencyLists[vertex1].AdjacentNodes.head; node != NULL; node = node->next)
    {
        if (node->val.vertex == vertex2 && !node->val.isVirtual)
        {
            return 0;
        }
    }

    // use NodePath list to find the intermidate node
    for (Node<NodePath>* node = nodePaths->head; node != NULL; node = node->next)
    {
        if (node->val.vertex1 == vertex1 && node->val.vertex2 == vertex2)
        {
            return node->val.intermediateVertex;
        }
    }

    return -1;
}

/** Adds the edge connecting vertex1 and 
 *   vertex2 to a sorted list of edgelength lists
 * 
 *  The edges are grouped in lists with all edges of 
 *  a specified length in a list.  The edges in the
 *  list are sorted lexicographically. Given two edges (u, v)
 *   and (w, x), if u < w then (u, v) < (w, x); if u == w 
 *   then (u, v) < (w, x) if v < x.
 *  The lists themselves are sorted by weight which is
 *  the shortest lengths between the vertices 
 */
void Graph::AddEdge(int vertex1, int vertex2, int length)
{
    if (edgeLengths == NULL)
    {
        edgeLengths = new LinkedList<EdgeLength>();
    }

    Node<EdgeLength>* node = NULL;
    for (node = edgeLengths->head; node != NULL; node = node->next)
    {
        if (node->val.length == length)
        {
            Edge edge(vertex1, vertex2, length);
            InsertEdge(node->val.edgesList, edge);
            return;
        }
    }

    EdgeLength edgeLength;
    edgeLength.length = length;

    edgeLength.edgesList = new LinkedList<Edge>();

    Edge edge(vertex1, vertex2, length);
    InsertEdge(edgeLength.edgesList, edge);

    Node<EdgeLength>* edgeLengthNode = edgeLengths->head;
    for (Node<EdgeLength>* prevNode = edgeLengthNode; edgeLengthNode != NULL; edgeLengthNode = edgeLengthNode->next)
    {
        if (edgeLength.length < edgeLengthNode->val.length)
        {
            if (edgeLengthNode == edgeLengths->head)
            {
                edgeLengths->InsertHead(edgeLength);
            }
            else
            {
                edgeLengths->InsertAfter(prevNode, edgeLength);
            }

            return;
        }

        prevNode = edgeLengthNode;
    }

    edgeLengths->AppendNode(edgeLength);
}

/** Inserts the edge in the edges list
 *  which is lexicographically sorted
 */
void Graph::InsertEdge(LinkedList<Edge>* edgesList, Edge edge)
{
    Node<Edge>* node = edgesList->head;
    for (Node<Edge>* prevNode = node; node != NULL; node = node->next)
    {
        Edge nodeEdge = node->val;

        if (edge < nodeEdge)
        {
            if (node == edgesList->head)
            {
                edgesList->InsertHead(edge);
            }
            else
            {
                edgesList->InsertAfter(prevNode, edge);
            }

            return;
        }

        prevNode = node;
    }

    edgesList->AppendNode(edge);
}

/** For the Euler circuit algorithm,
*  marks the vertices of the edge as 'used'
*
* @param1 edge  The edge in the graph
*/
void Graph::MarkVerticesAsUsed(Edge edge)
{
    // do it for vertex2
    for (Node<AdjacentNode>* node = adjacencyLists[edge.vertex1].AdjacentNodes.head; node != NULL; node = node->next)
    {
        if (node->val.vertex == edge.vertex2 && !node->val.isUsed)
        {
            node->val.isUsed = true;
            break;
        }
    }

    // do it for vertex1
    for (Node<AdjacentNode>* node = adjacencyLists[edge.vertex2].AdjacentNodes.head; node != NULL; node = node->next)
    {
        if (node->val.vertex == edge.vertex1 && !node->val.isUsed)
        {
            node->val.isUsed = true;
            break;
        }
    }
}

/** Returns the no. of vertices in the graph
 * 
 * @returns number of vertices
 */
int Graph::GetNumVertices()
{
    return numVertices;
}


/** Returns the no. of edges in the graph
 *
 * @returns number of edges 
 */
int Graph::GetNumEdges()
{
    return numEdges;
}


/** Prints adjacency lists of the graph
 */
void Graph::Print()
{
    if (adjacencyLists == NULL)
    {
        return;
    }

    for (int i = 1; i <= numVertices; i++)
    {
        std::cout << i << ": ";
        for (Node<AdjacentNode>* node = adjacencyLists[i].AdjacentNodes.head; node != NULL; node = node->next)
        {
            std::cout << "(" << node->val.vertex << "," << node->val.isUsed << ") ";
        }

        std::cout << std::endl;
    }
}

/** Prints the vertices that have
 *  odd number of edges
 */

void Graph::PrintOddVertices()
{
    std::cout << "The odd degree vertices in G: { O = { ";

    if (oddVertices != NULL)
    {
        oddVertices->Print();
    }

    std::cout << " } }" << std::endl;
}

/** Prints results of the Floyd-Warshall
 *  algorithm for odd vertices in the graph
 */
void Graph::PrintShortestPathOddVertices()
{
    std::cout << std::endl << "Results of Floyd-Warshall on O:" << std::endl;

    if (oddVertices == NULL || distanceMatrixOddVertices == NULL)
    {
        return;
    }

    std::cout << "     | ";

    for (int i = 1; i <= oddVertices->GetCount(); i++)
    {
        printf(" %3d", distanceMatrixOddVertices[0][i]);
    }

    std::cout << std::endl << "--- -+-";

    for (int i = 0; i < oddVertices->GetCount(); i++)
    {
        printf(" ---");
    }

    std::cout << std::endl;

    for (int row = 1; row <= oddVertices->GetCount(); row++)
    {
        printf("%3d  | ", distanceMatrixOddVertices[row][0]);

        for (int col = 1; col <= oddVertices->GetCount(); col++)
        {
            printf(" %3d", distanceMatrixOddVertices[row][col]);
        }

        std::cout << std::endl;
    }
}


/** Prints the matching list which contains
 * the matching vertices that were found using the Greedy
 * Algorithm
 */
void Graph::PrintGreedyPerfetcMatchingVertices()
{
    std::cout << std::endl << "The greedy perfect matching in O: M = { ";

    if (matching != NULL)
    {
        matching->Print();
    }

    std::cout << " }" << std::endl;
}

/** Prints the Euler circuit
 */
void Graph::PrintEulerCircuit()
{
    std::cout << std::endl << "The Euler circuit in G with virtual edges is:" << std::endl;

    if (eulerCircuit != NULL)
    {
        for (Node<Edge>* node = eulerCircuit->head; node != NULL; node = node->next)
        {
            std::cout << "\t" << node->val << std::endl;
        }
    }

    std::cout << std::endl;
}
