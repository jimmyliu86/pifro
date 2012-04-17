// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#ifndef _PIFRO2_INCLUDE_GREEDY_H_
#define _PIFRO2_INCLUDE_GREEDY_H_

#include <cmath>
#include <vector>
#include <iostream>
#include <cstdlib>

#include "./rvgs.h"
#include "./Graph.h"
#include "./Demand.h"
#include "./Dijkstra.h"
#include "./Functions.h"

using std::cout;

class Greedy {
  public:
    Functions functions;
    Greedy();
    explicit Greedy(int qtRequests);
    void setGDemand(Demand& demand);
    void setGGraph(Graph& graph);
    Demand getGDemand();
    Graph getGGraph();
    void setObjDijkstra(Dijkstra& objdijkstra);
    void DemandSort(std::vector<Request>& vecrequest);
    void DemandSwap(std::vector<Request>& vecrequest);
    float deletePath(Graph& graph,
                     int path,
                     int qtvertex,
                     int qtrequests);
    float addPath(Graph& graph,
                  int path,
                  int qtvertex,
                  int qtrequests);
    float execute(Graph& graph,
                  std::vector<Request>& vecrequest,
                  int qtvertex,
                  bool regenerateDijkstra);
    float executeWithRefine(Graph& graph,
                            std::vector<Request>& vecrequest);
    float executeWithRefine(Graph graph,
                            std::vector<Request> vecrequest,
                            std::vector<int> permutation);

  private:
    Graph GGraph;
    Demand GDemand;
    float MinCost;
    Dijkstra ObjDijkstra;
};

#endif  // _PIFRO2_INCLUDE_GREEDY_H_
