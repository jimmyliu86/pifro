#include "dijkstra/graph.h"

#include <algorithm>
#include <cfloat>
#include <list>
#include <vector>

#include "dijkstra/heap.h"

using std::list;
using std::vector;

Graph::Graph(int n) : num_vertices_(n), forward_star_(n) {
}

Graph::Graph(int n, const list<Arc>& arcs) : num_vertices_(n),forward_star_(n) {
  for (list<Arc>::const_iterator it = arcs.begin(); it != arcs.end(); it++) {
    forward_star_[it->u].push_back(std::make_pair(it->v, it->weight));
  }
}

void Graph::AddArc(int u, int v, float w) {
  forward_star_[u].push_back(std::make_pair(v, w));
}

void Graph::AddEdge(int u, int v, float w) {
  AddArc(u, v, w);
  AddArc(v, u, w);
}

float Graph::dijkstra(int s, int t, list<int> *path) {
  // Pai de cada vértice no caminho.
  int parent[num_vertices_];

  // Distância entre s e todos os vértices.
  float distance[num_vertices_];
  std::fill(distance, distance + num_vertices_, FLT_MAX);
  distance[s] = 0;

  // Calcula o caminho mais curto.
  Heap* H = HeapInit(num_vertices_);
  HeapInsert(H, s, distance[s]);
  while (HeapSize(H) != 0) {
    int i = HeapMin(H);
    if (i == t) break;  // Para quando encontra 't'.
    HeapDelMin(H);
    for (list<std::pair<int, float>>::iterator it = forward_star_[i].begin();
         it != forward_star_[i].end();
         it++) {
      int j = it->first;
      float value = distance[i] + it->second;
      if (distance[j] > value) {
        parent[j] = i;
        if (distance[j] == FLT_MAX) {
          distance[j] = value;
          HeapInsert(H, j, value);
        } else {
          distance[j] = value;
          HeapDecKey(H, j, value);
        }
      }
    }
  }
  HeapFree(H);

  // Armazena o caminho mais curto em 'path',
  // caso este tenho sido passado como parâmetro.
  if (path != NULL) {
    path->push_front(t);
    while (path->front() != s) {
      path->push_front(parent[path->front()]);
    }
  }
  return distance[t];
}
