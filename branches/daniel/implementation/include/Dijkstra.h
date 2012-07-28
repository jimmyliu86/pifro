// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#ifndef _PIFRO2_INCLUDE_DIJKSTRA_H_
#define _PIFRO2_INCLUDE_DIJKSTRA_H_

#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <float.h>

#include "./macros.h"
#include "./graph.h"
#include "./request.h"
#include "./vertex.h"
#include "./functions.h"
#include "./constants.h"

using std::cout;
using std::endl;

class Dijkstra {
  public:
    std::vector<std::vector<int> > paths_;

    Dijkstra();
    explicit Dijkstra(int qtpaths);
    Graph GetPathByDijkstra(Graph graph,
                            int src,
                            int dst,
                            int idpath,
                            int qtrequests);
    void DeletePath(int idpath);
    Graph SetAllGraphEdgeIncCost(Graph graph, int qtrequests);
    Graph SetAllGraphEdgeIncCost(Graph graph, int qtrequests, int p);
    void PrintPaths();

  private:
    float cost_by_dijkstra_;
};

#endif  // _PIFRO2_INCLUDE_DIJKSTRA_H_
