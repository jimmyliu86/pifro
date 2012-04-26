// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#include <vector>

#include "./graph.h"

Graph::Graph() {
}

Graph::Graph(char* filename, int tipo) {
  if (tipo == 0)
    LoadFromSNDFile(filename);
}

std::vector<Vertex>*& Graph::GetAdjList() {
  return adj_list_;
}

int**& Graph::GetAdjMatrix() {
  return adj_matrix_;
}

int Graph::GetQtVertex() {
  return qt_vertex_;
}

void Graph::SetAdjList(std::vector<Vertex>* adjlist) {
  adj_list_ = adjlist;
}

void Graph::SetQtVertex(int qtvertex) {
  qt_vertex_ = qtvertex;
}

void Graph::AddEdge(int src, int dst, float weight) {
  Vertex vsrc(src, 0, weight);
  Vertex vdst(dst, 0, weight);
  // AdjList[src].push_back(AdjList[dst][0]);
  // AdjList[src][0].setWeight(weight);
  adj_list_[src].push_back(vdst);
  // AdjList[dst].push_back(AdjList[src][0]);
  // AdjList[dst][0].setWeight(weight);
  adj_list_[dst].push_back(vsrc);
  adj_matrix_[src][dst] = weight;
  adj_matrix_[dst][src] = weight;
}

std::vector<Vertex>& Graph::GetNeighbors(int vertex) {
  return adj_list_[vertex];
}

void Graph::LoadFromSNDFile(char* filename) {
  ifstream fin(filename);
  fin >> qt_vertex_;
  fin >> qt_edge_;
  adj_list_ = new std::vector<Vertex>[qt_vertex_];
  adj_matrix_ = new int*[qt_vertex_];
  Vertex tmp(0, 0, 0);
  for (int i = 0; i < qt_vertex_; i++) {
    tmp.SetNumber(i);
    adj_list_[i].push_back(tmp);

    adj_matrix_[i] = new int[qt_vertex_];
    for (int x = 0; x < qt_vertex_; x++) {
      adj_matrix_[i][x] = -1;
    }
  }

  int src = 0, dst = 0;
  float weight = 0;

  for (int i = 1; i < qt_vertex_; i++) {
    fin >> src;
    fin >> dst;
    fin >> weight;
    // double weightr = roundIt(weight, pow(10,-2));
    AddEdge(src, dst, weight);
  }

  fin.close();
}

float Graph::GetTotalCost() {
  float totalcost = 0;
  for (int p = 0; p < qt_vertex_; p++) {
    for (int x = 1; x < adj_list_[p].size(); x++) {
      // cout << "TOTALCOST: " << graph.getAdjList()[p][x].getCost() << endl;
      if (adj_list_[p][x].GetColor() == -1) {
        totalcost += adj_list_[p][x].GetCost();
        adj_list_[p][x].SetColor(0);
        // Reverso
        // cout << "Somado : " << AdjList[p][0].getNumber()
        // << " - " << AdjList[p][x].getNumber() << " - "
        // << AdjList[p][x].getCost() << endl;
        int u = 1;
        while (u < adj_list_[adj_list_[p][x].GetNumber()].size()) {
          if (adj_list_[adj_list_[p][x].GetNumber()][u].GetNumber() ==
                                   adj_list_[p][0].GetNumber()) {
            adj_list_[adj_list_[p][x].GetNumber()][u].SetColor(0);
            // cout << "Ignorando : "
            // << AdjList[AdjList[p][x].getNumber()][0].getNumber()
            // << " - " << AdjList[AdjList[p][x].getNumber()][u].getNumber()
            // << " - Custo:" << AdjList[AdjList[p][x].getNumber()][u].getCost()
            // << endl;
            // break;
          }
          u++;
        }
      }
    }
  }
  CleanColors();

  return totalcost;
}

void Graph::CleanCosts() {
  for (int i = 0; i < qt_vertex_; i++) {
    for (int x = 1; x < adj_list_[i].size(); x++) {
      // cout  << "->" << AdjList[i][x].getWeight()
      // << "->" << "[" << AdjList[i][x].getNumber() << "] ";
      adj_list_[i][x].SetCost(0);
      adj_list_[i][x].SetIncCost(0);
    }
    // cout << endl;
  }
}

void Graph::CleanColors() {
  for (int i = 0; i < qt_vertex_; i++) {
    for (int x = 1; x < adj_list_[i].size(); x++) {
      // cout  << "->" << AdjList[i][x].getWeight()
      // << "->" << "[" << AdjList[i][x].getNumber()
      // << "] ";
      adj_list_[i][x].SetColor(-1);
    }
    // cout << endl;
  }
}

void Graph::Print() {
  for (int i = 0; i < qt_vertex_; i++) {
    for (int x = 0; x < adj_list_[i].size(); x++) {
      cout  << "[" << adj_list_[i][x].GetNumber() << "]->";
    }
    cout << endl;
  }
}

void Graph::PrintWithWeight() {
  cout << "ADJLIST:" << endl << endl;
  for (int i = 0; i < qt_vertex_; i++) {
    cout << "[" << adj_list_[i][0].GetNumber() << "]";
    for (int x = 1; x < adj_list_[i].size(); x++) {
      cout  << "->" << adj_list_[i][x].GetWeight()
            << "->" << "[" << adj_list_[i][x].GetNumber()
            << "] ";
    }
    cout << endl;
  }

  cout << endl << endl << "ADJMATRIX:" << endl << endl;
  cout << "     ";
  for (int i = 0; i < qt_vertex_; i++) {
    cout << "\t[" << i << "]";
  }
  cout << endl;

  for (int i = 0; i < qt_vertex_; i++) {
    cout << "[" << i << "]";
    for (int x = 0; x < qt_vertex_; x++) {
      cout << "\t" << adj_matrix_[i][x];
    }
    cout << endl;
  }
}

void Graph::PrintWithCost() {
  cout << endl << endl << "ADJLIST:" << endl << endl;
  for (int i = 0; i < qt_vertex_; i++) {
    cout << "[" << adj_list_[i][0].GetNumber() << "]";
    for (int x = 1; x < adj_list_[i].size(); x++) {
      cout  << "->" << adj_list_[i][x].GetCost()
            << "->" << "[" << adj_list_[i][x].GetNumber()
            << "] ";
    }
    cout << endl;
  }
}

void Graph::PrintWithIncCost() {
  cout << endl << endl << "ADJLIST:" << endl << endl;
  for (int i = 0; i < qt_vertex_; i++) {
    cout << "[" << adj_list_[i][0].GetNumber() << "]";
    for (int x = 1; x < adj_list_[i].size(); x++) {
      cout  << "->" << adj_list_[i][x].GetIncCost()
            << "->" << "[" << adj_list_[i][x].GetNumber()
            << "] ";
    }
    cout << endl;
  }
}

void Graph::PrintWithQtRequests() {
  cout << endl << endl << "ADJLIST:" << endl << endl;
  for (int i = 0; i < qt_vertex_; i++) {
    cout << "[" << adj_list_[i][0].GetNumber() << "]";
    for (int x = 1; x < adj_list_[i].size(); x++) {
      cout  << "->" << adj_list_[i][x].GetQtRequests()
            << "->" << "[" << adj_list_[i][x].GetNumber()
            << "]";
    }
    cout << endl;
  }
}
