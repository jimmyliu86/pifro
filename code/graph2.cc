#include "graph2.h"

#include <cassert>
#include <cfloat>

Graph::Graph() {
}

Graph::~Graph() {
}

Graph::Graph(const Graph& other) {
  int size = other.Size();
    
  this->Init(size);
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      this->Link(i, j, other.Weight(i, j));
    }
  }
}

Graph &Graph::operator=(const Graph& other) {
  if (this != &other) {
    int size = other.Size();
    
    this->Init(size);
    for (int i = 0; i < size; ++i) {
      for (int j = 0; j < size; ++j) {
        this->Link(i, j, other.Weight(i, j));
      }
    } 
  }
  return *this;
}

void Graph::Init(int size) {
  assert(size > 0);

  links_.resize(size);
  for (int i = 0; i < size; ++i) {
    links_[i].resize(size);
    
    for (int j = 0; j < size; ++j) {
      links_[i][j] = DBL_MAX;
    }
  }
}

int Graph::Size() const {
  return links_.size(); 
}

void Graph::Link(int from, int to, double weight) {
  links_[from][to] = weight;
}

void Graph::Unlink(int from, int to) {
  links_[from][to] = DBL_MAX;
}

bool Graph::IsLinked(int from, int to) const {
  return links_[from][to] != DBL_MAX; 
}

double Graph::Weight(int from, int to) const {
  return links_[from][to];
}

std::vector<int> Graph::Neighbors(int node) const {
  int size = links_.size();
  std::vector<int> neighbors;
  
  for (int i = 0; i < size; ++i) {
    if (IsLinked(node, i)) {
      neighbors.push_back(i);
    }
  }
}