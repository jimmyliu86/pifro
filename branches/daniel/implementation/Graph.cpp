#include "./Graph.h"
#include <list>

#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

Graph::Graph()
{
}
Graph::Graph(char* filename, int tipo)
{
    if(tipo == 0)
    {
        loadFromSNDFile(filename);
    }
}

std::vector<Vertex>*& Graph::getAdjList()
{
    return AdjList;
}

int Graph::getQtVertex()
{
    return QtVertex;
}

void Graph::setAdjList(std::vector<Vertex>* adjlist)
{
    AdjList = adjlist;
}

void Graph::setQtVertex(int qtvertex)
{
    QtVertex = qtvertex;
}

void Graph::addEdge(int src, int dst, float weight)
{
    //AdjList[src].push_back(vertex);
    AdjList[dst][0].setWeight(weight);
    AdjList[src].push_back(AdjList[dst][0]);
    AdjList[src][0].setWeight(weight);
    AdjList[dst].push_back(AdjList[src][0]);
}

std::vector<Vertex> Graph::getNeighbors(int vertex)
{
    return AdjList[vertex];
}

void Graph::loadFromSNDFile(char* filename)
{
    ifstream fin(filename);
    fin >> QtVertex;
    fin >> QtEdge;
    AdjList = new std::vector<Vertex>[QtVertex];
    Vertex tmp(0,0,0);
    for(int i=0; i<QtVertex; i++)
    {
        tmp.setNumber(i);
        AdjList[i].push_back(tmp);
    }

    int src = 0, dst = 0;
    float weight = 0;

    for(int i=0; i<QtEdge; i++)
    {
        fin >> src;
        fin >> dst;
        fin >> weight;
        addEdge(src, dst, weight);
    }

    fin.close();
}

void Graph::print()
{
    for(int i=0; i<QtVertex; i++)
    {
        for(int x=0; x<AdjList[i].size(); x++)
        {
            cout  << "[" << AdjList[i][x].getNumber() << "]->";
        }
        cout << endl;
    }
}

void Graph::printWithWeight()
{
    for(int i=0; i<QtVertex; i++)
    {
        cout << "[" << AdjList[i][0].getNumber() << "]";
        for(int x=1; x<AdjList[i].size(); x++)
        {
            cout  << "->" << AdjList[i][x].getWeight() << "->" << "[" << AdjList[i][x].getNumber() << "] ";
        }
        cout << endl;
    }
}
