#ifndef PIFRO_HEURISTICS_H_
#define PIFRO_HEURISTICS_H_

#include "./Macros.h"
#include "./Vertex.h"
#include "./Links.h"
#include "./Graph.h"

#include <vector>

class Heuristics{
      public:
             Graph getGraph();
             void setGraph(Graph graph);
             std::vector<int> BFS(int src, int dst);
             
             
             
             
             
      private:
              Graph objGraph;
              
              
              
              
              
};
#endif
