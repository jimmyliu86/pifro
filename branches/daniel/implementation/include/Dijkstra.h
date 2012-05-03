// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#ifndef _PIFRO2_INCLUDE_DIJKSTRA_H_
#define _PIFRO2_INCLUDE_DIJKSTRA_H_

#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>

#include "./macros.h"
#include "./graph.h"
#include "./request.h"
#include "./vertex.h"
#include "./functions.h"

using std::cout;
using std::endl;

class Dijkstra {
  public:
    std::vector<std::vector<int> > paths_;

    Dijkstra();
    explicit Dijkstra(int qtpaths);
    Graph GetCostByDijkstra(Graph& graph,
                            int src,
                            int dst,
                            int idpath);
    void DeletePath(int idpath);
    void SetCostByDijkstra(float cost);
    Graph SetAllGraphEdgeIncCost(Graph& graph, int qtrequests);
    void PrintPaths();
  private:
    float cost_by_dijkstra_;

};

#endif  // _PIFRO2_INCLUDE_DIJKSTRA_H_
