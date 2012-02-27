#ifndef PIFRO_DIJKSTRA_H_
#define PIFRO_DIJKSTRA_H_

#include "./Macros.h"
#include "./Graph.h"
#include "./Request.h"
#include "./Vertex.h"

class Dijkstra{

      public:
             Dijkstra();
             Dijkstra(int qtpaths);
             float getCostByDijkstra(std::vector<Vertex>* adjlist, int qtvertex, int src, int dst, int idpath);
             void DeletePath(int idpath);
             void setCostByDijkstra(float cost);

      private:
             float CostByDijkstra;
             std::vector<int>* Paths;

};

#endif
