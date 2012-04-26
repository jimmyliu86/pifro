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
#include "./graph.h"
#include "./demand.h"
#include "./dijkstra.h"
#include "./functions.h"

using std::cout;

class Greedy {
  public:
    Functions functions_;
    Greedy();
    explicit Greedy(int qtRequests);
    void SetDemand(Demand& demand);
    void SetGraph(Graph& graph);
    void SetDijkstra(Dijkstra& dijkstra);
    Demand GetDemand();
    Graph GetGraph();
    void DemandSort(std::vector<Request>& vecrequest);
    void DemandSwap(std::vector<Request>& vecrequest);
    float DeletePath(Graph& graph,
                     int path,
                     int qtvertex,
                     int qtrequests);
    float AddPath(Graph& graph,
                  int path,
                  int qtvertex,
                  int qtrequests);
    float Execute(Graph& graph,
                  std::vector<Request>& vecrequest,
                  int qtvertex,
                  bool regenerateDijkstra);
    float ExecuteWithRefine(Graph& graph,
                            std::vector<Request>& vecrequest);
    float ExecuteWithRefine(Graph graph,
                            std::vector<Request> vecrequest,
                            std::vector<int> permutation);

  private:
    Graph graph_;
    Demand demand_;
    float min_cost_;
    Dijkstra dijkstra_;
};

#endif  // _PIFRO2_INCLUDE_GREEDY_H_
