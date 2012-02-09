#ifndef PIFRO_GREEDY_H_
#define PIFRO_GREEDY_H_

#include "./Macros.h"
#include "./Graph.h"
#include "./Request.h"
#include "./Vertex.h"
#include "./Demand.h"
#include "./Dijkstra.h"

#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <queue>
#include <time.h>
#include <string.h>

#include "./Comparision.h"
using namespace std;

class Greedy{
      
      public:
             Greedy();
             void setGDemand(Demand& demand);
             void setGDijkstra(Dijkstra dijkstra);
             void setGGraph(Graph& graph);
             Demand getGDemand();
             Dijkstra getGDijkstra();
             Graph getGGraph();
             
             void DemandSort(std::vector<Request>& vecrequest);
             float execute(std::vector<Vertex>*& adjlist, std::vector<Request>& vecrequest, int qtvertex, int time);
      
      private:
              Graph GGraph;
              Demand GDemand;
              Dijkstra GDijkstra;
};

#endif
