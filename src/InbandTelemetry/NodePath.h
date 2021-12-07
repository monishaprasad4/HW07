/** NodePath.h
 *  Definition of the NodePath class
 */

#pragma once

#include<iostream>

class NodePath
{
public:

    NodePath();
    NodePath(int v1, int v2, int intermediate);
    int vertex1;
    int vertex2;
    int intermediateVertex;

    friend std::ostream& operator<< (std:: ostream& os, const NodePath& nodePath);
};

