#ifndef PIFRO_DIJKSTRA_H_
#define PIFRO_DIJKSTRA_H_

#include "./Macros.h"
#include "./Graph.h"
#include "./Request.h"
#include "./Vertex.h"
#include "./Functions.h"

class Dijkstra{

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

#endif
