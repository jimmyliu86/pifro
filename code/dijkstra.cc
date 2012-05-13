#include "dijkstra.h"

#include <cstdio>
#include <cfloat>
#include <cassert>

#include <algorithm>
#include <list>

class Node {
 public:
  int p;
  double w;
};


bool sortNodeFunction(Node i, Node j) {
  return (i.w > j.w);
}

Dijkstra::Dijkstra() {
}

Dijkstra::~Dijkstra() {
}

void Dijkstra::set_graph(const Graph &graph) {
  graph_ = graph;
}

Graph Dijkstra::graph() const {
  return graph_;
}

void Dijkstra::Calculate(int from) {
  from_ = from;
  
  int size = graph_.Size();
  
  distance_.clear();
  previous_.clear();
  distance_.resize(size);
  previous_.resize(size);
  
  for (int i = 0; i < size; ++i) {
    distance_[i] = DBL_MAX;
    previous_[i] = -1;
  }
  
  distance_[from] = 0.0;
  previous_[from] = -1;
  
  std::vector<Node> destination;
  for (int i = 0; i < size; ++i) {
    
    Node n;
    n.p = i;
    n.w = DBL_MAX;
    
    destination.push_back(n);
  }
  destination[from].w = 0;

  Node current; 
  int update = 0;
  
  // sort
  std::sort(destination.begin(), destination.end(), sortNodeFunction);
  
  while (!destination.empty()) {
    current = destination.back();
    if (distance_[current.p] == DBL_MAX) {
      break;
    }
    
    destination.pop_back();
    
    for (int i = 0; i < size; ++i) {
      if (graph_.IsLinked(current.p, i)) {
        update = distance_[current.p] + graph_.Weight(current.p, i);
        if (update < distance_[i]) {
          distance_[i] = update;
          previous_[i] = current.p;

          for (std::vector<Node>::iterator it = destination.begin(); it != destination.end(); ++it) {
	    if (it->p == i) {
	      it->w = update;
	      break; 
	    }
          }
          std::sort(destination.begin(), destination.end(), sortNodeFunction);
        }
      }
    }
  }
}

std::vector<int> Dijkstra::Path(int to) {
  assert(from_ != to);
  std::vector<int> reverse_path;
  
  int current = to;
  while (current != -1) {
    reverse_path.push_back(current);
    current = previous_[current];
  }
  std::vector<int> path(reverse_path.rbegin(), reverse_path.rend());
  return path;
}

double Dijkstra::Weight(int to) {
  return distance_[to];
}

void Dijkstra::Print() {
  std::vector<int> path;
  for (int i = 0; i < graph_.Size(); ++i) {
     if (from_ == i) continue;
     fprintf(stderr, "From %d to %d\n", from_, i);
     path = Path(i);
     fprintf(stderr, "%d\n", static_cast<int>(path.size()));
     for (int j = 0; j < path.size(); ++j) {
       fprintf(stderr, "%d | ", path[j]);       
     }
     fprintf(stderr, "\n");
  }
}
