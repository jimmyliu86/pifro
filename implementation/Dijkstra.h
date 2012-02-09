#ifndef PIFRO_DIJKSTRA_H_
#define PIFRO_DIJKSTRA_H_

#include "./Macros.h"
#include "./Graph.h"
#include "./Request.h"
#include "./Vertex.h"

class Dijkstra{
      
      public:
             Dijkstra();
             float getCostByDijkstra(std::vector<Vertex>* adjlist, int qtvertex, int src, int dst);
             void setCostByDijkstra(float cost);
             
      private:
             float CostByDijkstra;
              
              
};

#endif
