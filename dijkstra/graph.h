#ifndef BRANCHES_DANIEL_DIJKSTRA_GRAPH_H_
#define BRANCHES_DANIEL_DIJKSTRA_GRAPH_H_

#include <list>
#include <vector>
#include <utility>

struct Arc {
  int u;  // Vértice de origem do arco.
  int v;  // Vértice de destino do arco.
  float weight;  // Peso do arco.
  Arc(int a, int b, int w) : u(a), v(b), weight(w) {}  // Construtor.
};

class Graph {
 private:
  // Número de vértices.
  int num_vertices_;

  // Lista de adjacências direcionada do grafo.
  // forward_star_[u] armazena a lista de vizinhos de 'u'.
  // Cada elemento em forward_star_[u] é um 'pair' <v, weight(u,v)>.
  std::vector<std::list<std::pair<int, float>>> forward_star_;

 public:
  // Constrói um grafo direcionado com 'n' vértices e nenhum arco.
  Graph(int n);

  // Constrói um grafo direcionado com 'n' vértices e com os arcos em 'arcs'.
  Graph(int n, const std::list<Arc>& arcs);

  // Adiciona um arco '(u, v)' com peso 'w'.
  void AddArc(int u, int v, float w);

  // Adiciona uma aresta '[i, j]' com peso 'w'.
  void AddEdge(int u, int v, float w);

  // Retorna o caminho mais curto entre dois terminais (usando Reverse
  // Dijkstra).  Os vértices no caminho são retornados através de path, caso
  // este tenha sido passado como parâmetro.
  float dijkstra(int s, int t, std::list<int>* path = NULL);
};

#endif  // BRANCHES_DANIEL_DIJKSTRA_GRAPH_H_
