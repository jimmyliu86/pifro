#include "./Heuristics.h"

#include <vector>
Graph Heuristics::getGraph(){
      return objGraph;
}

void Heuristics::setGraph(Graph graph){
     objGraph = graph;
}

std::vector<int> BFS(int src, int dst){
                 //int qtvertex = getGraph().getQtVertex();
                 std::vector<Vertex>* adjlist;
                 //adjlist = getGraph().getAdjList();
//                 adjlist[src];
}
