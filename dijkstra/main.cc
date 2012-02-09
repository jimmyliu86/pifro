/*******************************************************************************
 *
 * Este programa é um exemplo de como usar a classe Graph implementada em
 * graph.h. Esta classe foi desenvolvida especialmente para executar o algoritmo
 * de dijkstra.
 *
 ******************************************************************************/

#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <vector>

#include "./graph.h"

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::list;
using std::string;
using std::stringstream;
using std::vector;

// Retorna uma string representando um caminho no formato "[s x y z t]".
string ToString(const list<int>& path) {
  stringstream sout;
  sout << "[ ";
  for (list<int>::const_iterator it = path.begin(); it != path.end(); it++) {
    sout << *it << " ";
  }
  sout << "]";
  return sout.str();
}

int main(int argc, char** argv) {
  if (argc != 2) {
    cerr << "./" << argv[0] << " <caminho_da_instancia>";
    exit(1);
  }

  ifstream fin(argv[1]);  // Arquivo com o grafo.
  int n;  // Número de vértices.
  int m;  // número de arestas.
  fin >> n >> m;
  Graph g(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    float w;
    fin >> u >> v >> w;
    g.AddEdge(u, v, w);
  }

  for (int i = 0; i < n; i ++) {
    for (int j = i + 1; j < n; j ++) {
      list<int> path;  // Vértices no caminho.
      float cost = g.dijkstra(i, j, &path);
      cout << "SP(" << i << "," << j << ") = "
           << ToString(path)
           << " --- custo = " << cost << endl;
    }
  }
}
