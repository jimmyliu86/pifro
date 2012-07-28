// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#ifndef _PIFRO2_INCLUDE_GRAPH_H_
#define _PIFRO2_INCLUDE_GRAPH_H_

#include <vector>
#include <iostream>
#include <fstream>

#include "./macros.h"
#include "./vertex.h"
#include "./functions.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

class Graph {
  public:
    std::vector< std::vector<Vertex> > adj_list_;
    int** adj_matrix_;
    int qt_vertex_;
    int qt_edge_;
    Functions functions_;
    int impossible_;

    Graph();
    explicit Graph(char* filename, int tipo);
    void AddEdge(int src, int dst, float weight);
    void DeleteEdge(int vertex);
    float GetTotalCost();
    void CleanCosts();
    void CleanColors();
    void LoadFromSNDFile(char* filename);
    void Print();
    void PrintWithWeight();
    void PrintWithCost();
    void PrintWithIncCost();
    void PrintWithQtRequests();
};

#endif  // _PIFRO2_INCLUDE_GRAPH_H_
