#ifndef PIFRO2_DIJKSTRA_H_
#define PIFRO2_DIJKSTRA_H_

#include "Macros.h"
#include "Graph.h"
#include "Request.h"
#include "Vertex.h"
#include "Functions.h"

#include <string.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <queue>
#include <algorithm>

using namespace std;

class Dijkstra {

public:
  //std::vector<Vertex>* Paths;
  vector<vector<int> > Paths;

  Dijkstra();
  Dijkstra(int qtpaths);
  float getCostByDijkstra(std::vector<Vertex>*& adjlist, int qtvertex, int src, int dst, int idpath);
  void DeletePath(int idpath);
  void setCostByDijkstra(float cost);
  void setAllGraphEdgeIncCost(Graph& graph, int qtvertex, int qtrequests);

private:
  float CostByDijkstra;

};

#endif //PIFRO2_DIJKSTRA_H_
