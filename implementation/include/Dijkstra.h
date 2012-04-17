// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#ifndef _PIFRO2_INCLUDE_DIJKSTRA_H_
#define _PIFRO2_INCLUDE_DIJKSTRA_H_

#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>

#include "./Macros.h"
#include "./Graph.h"
#include "./Request.h"
#include "./Vertex.h"
#include "./Functions.h"

using std::cout;
using std::endl;

class Dijkstra {
  public:
    std::vector<std::vector<int> > Paths;

    Dijkstra();
    explicit Dijkstra(int qtpaths);
    float getCostByDijkstra(std::vector<Vertex>*& adjlist,
                            int qtvertex,
                            int src,
                            int dst,
                            int idpath);
    void DeletePath(int idpath);
    void setCostByDijkstra(float cost);
    void setAllGraphEdgeIncCost(Graph& graph, int qtvertex, int qtrequests);
  private:
    float CostByDijkstra;

};

#endif  // _PIFRO2_INCLUDE_DIJKSTRA_H_
