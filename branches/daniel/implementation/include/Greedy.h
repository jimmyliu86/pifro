#ifndef PIFRO2_GREEDY_H_
#define PIFRO2_GREEDY_H_

#include "rvgs.h"
#include "Macros.h"
#include "Graph.h"
#include "Request.h"
#include "Vertex.h"
#include "Demand.h"
#include "Dijkstra.h"
#include "Functions.h"
#include "Comparision.h"

#include <cmath>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <queue>
#include <time.h>
#include <string.h>
#include <algorithm>

using namespace std;

class Greedy {

public:
  Functions functions;
  Greedy();
  Greedy(int qtRequests);
  void setGDemand(Demand& demand);
  void setGGraph(Graph& graph);
  Demand getGDemand();
  Graph getGGraph();
  void setObjDijkstra(Dijkstra& objdijkstra);


  void DemandSort(std::vector<Request>& vecrequest);
  void DemandSwap(std::vector<Request>& vecrequest);
  float deletePath(Graph& graph, int path, int qtvertex, int qtrequests);
  float addPath(Graph& graph, int path, int qtvertex, int qtrequests);
  float execute(Graph& graph, std::vector<Request>& vecrequest, int qtvertex, bool regenerateDijkstra);
  float executeWithRefine(Graph& graph, std::vector<Request>& vecrequest);
  float executeWithRefine(Graph graph, std::vector<Request> vecrequest, std::vector<int> permutation);

private:
  Graph GGraph;
  Demand GDemand;
  float MinCost;
  Dijkstra ObjDijkstra;
};

#endif //PIFRO2_GREEDY_H_
