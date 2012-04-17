// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#include <vector>

#include "./Dijkstra.h"

Dijkstra::Dijkstra() {
}

Dijkstra::Dijkstra(int qtpaths) {
  // Paths = new std::vector<Vertex>[qtpaths];
  // Paths = new std::vector<int>[qtpaths];

  /* vector<int> tmp;
  for(int i=0;i<qtpaths;i++); */
  Paths.resize(qtpaths);
}

float Dijkstra::getCostByDijkstra(std::vector<Vertex>*& adjlist,
                                  int qtvertex,
                                  int src,
                                  int dst,
                                  int idpath) {
  /* int src = 0, dst = 0;
  if(vdst < vsrc)
  {
    dst = vsrc;
    src = vdst;
  }else{
    src = vsrc;
    dst = vdst;
  } */
  const int k = qtvertex;
  int vis[k], prev[k];
  float dis[k];
  // Vertex prev[qtvertex];
  memset(vis, 0, sizeof(vis));
  memset(dis, 0x7f, sizeof(dis));
  memset(prev, -1, sizeof(prev));

  dis[src] = 0;

  while (true) {
    int i, n = -1;

    for (i = 0; i < qtvertex; i++)
      if (!vis[i] && (n < 0 || dis[i] < dis[n]))
        n = i;

    if (n < 0)
      break;
    vis[n] = 1;

    for (i = 1; i < adjlist[n].size(); i++)
      // Aresta n -> LAdj[n][i].first com custo LAdj[n][i].second
      /* if (dis[adjlist[n][i].getNumber()] > dis[n] + adjlist[n][i].getWeight()){
              dis[adjlist[n][i].getNumber()] = dis[n] + adjlist[n][i].getWeight();
              prev[adjlist[n][i].getNumber()] = n;
      } */
      if (dis[adjlist[n][i].getNumber()] >
                    dis[n] + adjlist[n][i].getIncCost()) {
        dis[adjlist[n][i].getNumber()] =
                    dis[n] + adjlist[n][i].getIncCost();
        // Vertex v(n,0,0);
        prev[adjlist[n][i].getNumber()] = n;
      }
  }


  // Vetor de distancias
  /* cout << "Distance: " << endl;
  for(int i = 0; i<qtvertex; i++){
              cout << "Posicao: " << i << " - " << dis[i] << " - " << endl;
  }
  cout << endl << endl;     */

  // Vetor de antecessores




  // cout << endl << "Requisition -
  // [SRC: " << src << " - DST: " << dst << "] : \n";
  int tmp = dst;




  // cout << "PRED: " << pred[dst-1] << endl;
  // cout << "Predecessor: ";
  std::vector<int> dijpath;

  while (tmp != -1) {
    // cout << tmp << " - ";
    // Vertex v(tmp,0,dis[tmp]);
    // Paths[idpath].push_back(tmp);
    dijpath.push_back(tmp);
    // tmp = pred[tmp];
    tmp = prev[tmp];
  }

  reverse(dijpath.begin(), dijpath.end());




  /* if(Paths[idpath].size() > 0)
  {
      cout << "Before execution the path is: ";
      for(int i=0; i<Paths[idpath].size(); i++)
      {
           cout << Paths[idpath][i] << " - ";
      }
  }
  cout << endl; */



  Paths[idpath].clear();
  Paths[idpath] = dijpath;

  /* for(int p=0; p< dijpath.size(); p++)
  {
  Paths[idpath].push_back(dijpath[p]);
  } */





  /* cout << "After execution the path is: ";
  for(int i=0; i<Paths[idpath].size(); i++)
  {
       cout << Paths[idpath][i] << " - ";
  }
  cout << endl; */






  /* cout << "PATH: ";
  for(int i=0; i<Paths[idpath].size(); i++)
  {
      cout << Paths[idpath][i] << " ";
  } */
  // cout << endl;
  return dis[dst];
}

void Dijkstra::setAllGraphEdgeIncCost(Graph& graph,
                                      int qtvertex,
                                      int qtrequests) {
  Functions functions;
  for (int i = 0; i < qtvertex; i++) {
    for (int x = 1; x < graph.getAdjList()[i].size(); x++) {
      int w = graph.getAdjList()[i][x].getQtRequests();
      float l = graph.getAdjList()[i][x].getWeight();
      int a = qtrequests;
      graph.getAdjList()[i][x].
            setIncCost(functions.fwdm(w+a, l) - functions.fwdm(w, l));
      // graph.getAdjList()[i][x].setIncCost(functions.fwdm(w + a, l)) ;
    }
  }
}

void Dijkstra::setCostByDijkstra(float cost) {
}
