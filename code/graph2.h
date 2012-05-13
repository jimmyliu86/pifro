#ifndef PIFRO_GRAPH_H_
#define PIFRO_GRAPH_H_

#include <vector>

class Graph {
 public:
  Graph();
  ~Graph();
  
  Graph(const Graph& other);
  Graph &operator=(const Graph& other);
  
  void Init(int size);
  
  void Link(int from, int to, double weight);
  void Unlink(int from, int to);
  bool IsLinked(int from, int to) const;
  
  int Size() const;
  double Weight(int from, int to) const;
  std::vector<int> Neighbors(int node) const;
  
  Graph Clone() const;

 private:
  std::vector< std::vector<double> > links_;
};

#endif  // PIFRO_GRAPH_H_