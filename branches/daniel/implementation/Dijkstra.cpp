#include "./Dijkstra.h"

#include <string.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <queue>
using namespace std;

Dijkstra::Dijkstra(){
}

Dijkstra::Dijkstra(int qtpaths)
{
    Paths = new std::vector<int>[qtpaths];
}

float Dijkstra::getCostByDijkstra(std::vector<Vertex>* adjlist, int qtvertex, int src, int dst, int idpath){

      int dis[qtvertex], vis[qtvertex], prev[qtvertex];
      memset(vis,0,sizeof(vis));
      memset (dis, 0x7f, sizeof (dis));
      memset(prev, -1, sizeof(prev));

      dis[src] = 0;

      while (true)
      {
              int i, n = -1;

              for (i = 0; i < qtvertex; i++)
                      if (! vis[i] && (n < 0 || dis[i] < dis[n]))
                              n = i;

              if (n < 0)
                      break;
              vis[n] = 1;

              for (i = 0; i < adjlist[n].size (); i++)
                      // Aresta n -> LAdj[n][i].first com custo LAdj[n][i].second
                      /*if (dis[adjlist[n][i].getNumber()] > dis[n] + adjlist[n][i].getWeight()){
                              dis[adjlist[n][i].getNumber()] = dis[n] + adjlist[n][i].getWeight();
                              prev[adjlist[n][i].getNumber()] = n;
                      }*/
                      if (dis[adjlist[n][i].getNumber()] > dis[n] + adjlist[n][i].getIncCost()){
                              dis[adjlist[n][i].getNumber()] = dis[n] + adjlist[n][i].getIncCost();
                              prev[adjlist[n][i].getNumber()] = n;
                      }
        }


      //Vetor de distâncias
      /*cout << "Distance: " << endl;
      for(int i = 0; i<qtvertex; i++){
                  cout << "Posicao: " << i << " - " << dis[i] << " - " << endl;
      }
      cout << endl << endl;     */

      //Vetor de antecessores
      int tmp = dst;
      //cout << "PRED: " << pred[dst-1] << endl;
      cout << "Predecessor: ";

      while(tmp != -1){
                  cout << tmp << " - ";
                  Paths[idpath].push_back(tmp);
                  //tmp = pred[tmp];
                  tmp = prev[tmp];

      }
      cout << endl;

      return dis[dst];

}



void Dijkstra::setCostByDijkstra(float cost){
}
