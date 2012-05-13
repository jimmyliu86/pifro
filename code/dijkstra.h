#ifndef PIFRO_DIJKSTRA_H_
#define PIFRO_DIJKSTRA_H_

#include <vector>

#include "graph2.h"

class Dijkstra {
 public:
  Dijkstra();
  ~Dijkstra();

  void set_graph(const Graph &graph);
  Graph graph() const;
  
  void Calculate(int from);
  
  std::vector<int> Path(int to);
  double Weight(int to);
  
  void Print();
 private:
  Graph graph_;
  int from_;
  std::vector<double> distance_;
  std::vector<int> previous_;
};

#endif  // PIFRO_DIJKSTRA_H_ 