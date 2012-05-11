// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#ifndef _PIFRO2_INCLUDE_GREEDY_H_
#define _PIFRO2_INCLUDE_GREEDY_H_

#include <cmath>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <time.h>

#include "./rvgs.h"
#include "./graph.h"
#include "./demand.h"
#include "./dijkstra.h"
#include "./functions.h"

using namespace std;

#define myrand ((1 * rand())/(float)(RAND_MAX))

class Greedy {
  public:
    Functions functions_;
    Greedy();
    Greedy(Graph graph, Demand demand);
    Greedy(int qtRequests);
    void SetDemand(Demand demand);
    void SetGraph(Graph graph);
    void SetDijkstra(Dijkstra dijkstra);
    void SetMinCost(float min_cost);
    Demand GetDemand();
    Graph GetGraph();
    float getMinCost();
    void DemandSort();
    void DemandSwap();
    float DeletePath(int path,
                     int qtrequests);
    float AddPath(int path,
                  int qtrequests);
    float Execute(bool regenerateDijkstra, bool demandSort);
    float ExecuteWithRefine(bool regenerate_dijkstra, bool demand_sort);
    float ExecuteWithRefine(std::vector<int> permutation);
    float ExecuteWithRefine(int k);

  private:
    Graph graph_;
    Demand demand_;
    float min_cost_;
    Dijkstra dijkstra_;
};

#endif  // _PIFRO2_INCLUDE_GREEDY_H_
