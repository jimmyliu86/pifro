#ifndef GRAPH_H
#define GRAPH_H

#include "Vertex.h"

#include <vector>
#include <iostream>
#include <cstdlib>
using namespace std;

class Graph
{
    public:
        Graph();
        virtual ~Graph();
        void setVecvertex(vector<Vertex> vecvertex);
        vector<Vertex> getVecvertex();
        void addVertex(string name, float longitude, float latitude);
        void print();
    protected:
    private:
        vector<Vertex> VecVertex;

};

#endif // GRAPH_H
