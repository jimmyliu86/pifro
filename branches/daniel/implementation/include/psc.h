#ifndef _PIFRO2_INCLUDE_PSC_H_
#define _PIFRO2_INCLUDE_PSC_H_

#include <time.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <float.h>

#include "./rvgs.h"
#include "./graph.h"
#include "./demand.h"
#include "./dijkstra.h"
#include "./functions.h"

class PSC
{
  public:
    Graph graph_;
    Demand demand_;
    float min_cost_;
    Dijkstra dijkstra_;

    Functions functions_;
    PSC();
    PSC(Graph graph, Demand demand);
    explicit PSC(int qtRequests);
    void DemandSwap();
    float DeletePath(int path,
                     int qtrequests,
                     int p);
    float AddPath(int path,
                  int qtrequests,
                  bool search_new_path,
                  int p);
    float Execute(bool regenerateDijkstra, bool demandSort);
    float Execute(bool regenerateDijkstra, bool demandSort, time_t tstart, int tex);
    float ExecuteWithRefine(bool regenerate_dijkstra, bool demand_sort);
    float ExecuteWithRefine(bool regenerate_dijkstra, bool demand_sort, time_t tstart, int tex);
    float ExecuteWithRefine(std::vector<int> permutation, time_t tstart, int tex);
    float ExecuteWithRefine(int k);
    float ExecuteWithRefine(int k, time_t tstart, int tex);
};

#endif // _PIFRO2_INCLUDE_PSC_H_
