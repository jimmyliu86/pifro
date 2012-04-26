// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#include <queue>
#include <vector>

#include "./breadth_first.h"

BreadthFirst::BreadthFirst() {
}

float BreadthFirst::GetKmDistance() {
  return km_distance_;
}

std::vector<int> BreadthFirst::GetWay() {
  return way_;
}

void BreadthFirst::SetKmDistance(float kmdistance) {
  km_distance_ = kmdistance;
}

void BreadthFirst::SetWay(std::vector<int> way) {
  way_ = way;
}

int BreadthFirst::GetQtROADM(std::vector<Vertex>*& adjlist,
                             int src,
                             int dst,
                             int qtvertex) {
  // Limpando caminho
  way_.clear();
  // todos os vertices brancos
  for (int x = 0; x < qtvertex; x++) {
    adjlist[x][0].SetColor(0);
    adjlist[x][0].SetLevel(-1);
    adjlist[x][0].SetPrevious(-1);
  }

  adjlist[src][0].SetColor(1);
  // DUVIDA 1 - CONTO O PRIMEIRO NODO COMO UM HOP OU NAO?
  adjlist[src][0].SetLevel(1);
  std::queue<int> q;
  q.push(adjlist[src][0].GetNumber());

  int i = 1, f = 2, act = 0, viz = 0, iret = -1, wvalue = 0;
  bool found = false;
  std::vector<int> visited;

  while (!q.empty()) {
    act = q.front();
    q.pop();
    for (int w = 0; w < adjlist[act].size(); w++) {
      if (adjlist[adjlist[act][w].GetNumber()][0].GetColor() == 0) {
        adjlist[adjlist[act][w].GetNumber()][0].SetColor(1);
        adjlist[adjlist[act][w].GetNumber()][0].
                       SetLevel(adjlist[act][0].GetLevel() + 1);
        adjlist[adjlist[act][w].GetNumber()][0].SetPrevious(act);
        q.push(adjlist[act][w].GetNumber());
        visited.push_back(adjlist[act][w].GetNumber());
      }

      // ao concluir o caminho ate o vertice de destino,
      // faz-se o caminho reverso e amazena-se o caminho
      if (adjlist[adjlist[act][w].GetNumber()][0].GetNumber() == dst) {
        adjlist[adjlist[act][w].GetNumber()][0].SetColor(2);
        // vertice de destino encontrado, retornara a largura do mesmo
        iret = adjlist[adjlist[act][w].GetNumber()][0].GetLevel();
        found = true;
        wvalue = w;
        break;
      }
    }
    if (found) {
      break;
    }
    adjlist[act][0].SetColor(2);
  }

  // Vector com o caminho seguido
  std::vector<int> way;
  way.push_back(dst);
  float km = 0;
  for (int u = 0; u <
                  adjlist[visited[visited.size() - 1]][0].GetLevel() - 1; u++) {
    way.push_back(adjlist[way[u]][0].GetPrevious());
    km += CalculateDistance(adjlist[way[u]][0].GetNumber(),
                            adjlist[way[u]][0].GetPrevious(),
                            adjlist);
    // cout << "Vertice: " << adjlist[way[u]][0].getNumber() << endl;
  }
  SetKmDistance(km);
  // sort(way.begin(),way.end());
  SetWay(way);
  // cout << "TAMANHO: " << Way.size() << " ";
  return iret;
}

float BreadthFirst::CalculateDistance(int src,
                                      int dst,
                                      std::vector<Vertex>*& adjlist) {
  for (int i = 0; i < adjlist[src].size(); i++) {
    if (adjlist[src][i].GetNumber() == dst) {
      return adjlist[src][i].GetWeight();
    }
  }
}

void BreadthFirst::PrintWay() {
  for (int i = (way_.size()-1); i >= 0; i--) {
    cout << way_[i] << " -> ";
  }
  cout << " TOTAL DISTANCE (KM): " << km_distance_ << endl;
}
