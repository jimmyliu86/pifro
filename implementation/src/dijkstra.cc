// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#include <vector>

#include "./dijkstra.h"

Dijkstra::Dijkstra() {
}

Dijkstra::Dijkstra(int qtpaths) {
  paths_.resize(qtpaths);
}

Graph Dijkstra::GetPathByDijkstra(Graph graph,
                                  int src,
                                  int dst,
                                  int idpath) {
  const int k = graph.qt_vertex_;
  int vis[k], prev[k];
  float dis[k];
  memset(vis, 0, sizeof(vis));
  memset(dis, 0x7f, sizeof(dis));
  memset(prev, -1, sizeof(prev));

  dis[src] = 0;

  while (true) {
    int i, n = -1;

    for (i = 0; i < graph.qt_vertex_; i++)
      if (!vis[i] && (n < 0 || dis[i] < dis[n]))
        n = i;

    if (n < 0)
      break;
    vis[n] = 1;

    for (i = 1; i < graph.adj_list_[n].size(); i++) {
      if (dis[graph.adj_list_[n][i].number_] >
          dis[n] + graph.adj_list_[n][i].inc_cost_) {
        dis[graph.adj_list_[n][i].number_] =
          dis[n] + graph.adj_list_[n][i].inc_cost_;
        prev[graph.adj_list_[n][i].number_] = n;
      }
    }
  }
  int tmp = dst;
  std::vector<int> dijpath;

  while (tmp != -1) {
    dijpath.push_back(tmp);
    tmp = prev[tmp];
  }

  reverse(dijpath.begin(), dijpath.end());

  paths_[idpath].clear();
  paths_[idpath] = dijpath;

  return graph;
}

Graph Dijkstra::SetAllGraphEdgeIncCost(Graph graph,
                                       int qtrequests) {
  Functions functions;
  for (int i = 0; i < graph.qt_vertex_; i++) {
    for (int x = 1; x < graph.adj_list_[i].size(); x++) {
      int w = graph.adj_list_[i][x].qt_requests_;
      float l = graph.adj_list_[i][x].weight_;
      int a = qtrequests;
      graph.adj_list_[i][x].
      inc_cost_ = functions.Fwdm(w+a, l) - functions.Fwdm(w, l);
    }
  }
  return graph;
}

void Dijkstra::PrintPaths() {
  for (int i = 0; i < paths_.size(); i++) {
    cout << endl << "PATH " << i << ": ";
    for (int x = 0; x < paths_[i].size(); x++) {
      cout << paths_[i][x] << " - ";
    }
  }
  cout << endl;
}
