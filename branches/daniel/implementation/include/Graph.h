// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#ifndef _PIFRO2_INCLUDE_GRAPH_H_
#define _PIFRO2_INCLUDE_GRAPH_H_

#include <vector>
#include <iostream>
#include <fstream>

#include "./Macros.h"
#include "./Vertex.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

class Graph {
  public:
    Graph();
    explicit Graph(char* filename, int tipo);
    std::vector<Vertex>*& getAdjList();
    int**& getAdjMatrix();
    int getQtVertex();
    void setAdjList(std::vector<Vertex>* adjlist);
    void setQtVertex(int qtvertex);
    void addEdge(int src, int dst, float weight);
    void deleteEdge(int vertex);
    std::vector<Vertex>& getNeighbors(int vertex);
    float getTotalCost();
    void cleanCosts();
    void cleanColors();
    void loadFromSNDFile(char* filename);
    void print();
    void printWithWeight();
    void printWithCost();
    void printWithIncCost();
    void printWithQtRequests();

  private:
    std::vector<Vertex>* AdjList;
    int** AdjMatrix;
    int QtVertex;
    int QtEdge;
};

#endif  // _PIFRO2_INCLUDE_GRAPH_H_
