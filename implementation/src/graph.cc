// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#include "./graph.h"

Graph::Graph() {
  impossible_ = -1;
}

Graph::Graph(char* filename, int tipo) {
  if (tipo == 0)
    LoadFromSNDFile(filename);
  impossible_ = -1;
}

void Graph::AddEdge(int src, int dst, float weight) {
  Vertex vsrc(src, 0, weight);
  Vertex vdst(dst, 0, weight);
  adj_list_[src].push_back(vdst);
  adj_list_[dst].push_back(vsrc);
  adj_matrix_[src][dst] = weight;
  adj_matrix_[dst][src] = weight;
}

void Graph::LoadFromSNDFile(char* filename) {
  ifstream fin(filename);
  fin >> qt_vertex_;
  fin >> qt_edge_;
  adj_list_.resize(qt_vertex_);
  adj_matrix_ = new int*[qt_vertex_];
  Vertex tmp(0, 0, 0);
  for (int i = 0; i < qt_vertex_; i++) {
    tmp.number_ = i;
    adj_list_[i].push_back(tmp);

    adj_matrix_[i] = new int[qt_vertex_];
    for (int x = 0; x < qt_vertex_; x++) {
      adj_matrix_[i][x] = -1;
    }
  }

  int src = 0, dst = 0;
  float weight = 0;

  for (int i = 1; i < qt_edge_; i++) {
    fin >> src;
    fin >> dst;
    fin >> weight;
    AddEdge(src, dst, weight);
  }

  fin.close();
}

float Graph::GetTotalCost() {
  float totalcost = 0;
  if(impossible_ != 0) {
    for (int p = 0; p < qt_vertex_; p++) {
      for (int x = 1; x < adj_list_[p].size(); x++) {
        if (adj_list_[p][x].color_ == -1) {
          int w = adj_list_[p][x].qt_requests_;
          float l = adj_list_[p][x].weight_;
          totalcost += functions_.Fwdm(w, l);
          adj_list_[p][x].color_ = 0;
          int u = 1;
          while (u < adj_list_[adj_list_[p][x].number_].size()) {
            if (adj_list_[adj_list_[p][x].number_][u].number_ ==
                adj_list_[p][0].number_) {
              adj_list_[adj_list_[p][x].number_][u].color_ = 0;
            }
            u++;
          }
        }
      }
    }
    CleanColors();
  } else {
    totalcost = -1;
  }
  return totalcost;
}

void Graph::CleanCosts() {
  for (int i = 0; i < qt_vertex_; i++) {
    for (int x = 1; x < adj_list_[i].size(); x++) {
      adj_list_[i][x].cost_ = 0;
      adj_list_[i][x].inc_cost_ = 0;
      adj_list_[i][x].qt_requests_ = 0;
      adj_list_[i][x].color_ = -1;
    }
  }
}

void Graph::CleanColors() {
  for (int i = 0; i < qt_vertex_; i++) {
    for (int x = 1; x < adj_list_[i].size(); x++) {
      adj_list_[i][x].color_ = -1;
    }
  }
}

void Graph::Print() {
  for (int i = 0; i < qt_vertex_; i++) {
    for (int x = 0; x < adj_list_[i].size(); x++) {
      cout  << "[" << adj_list_[i][x].number_ << "]->";
    }
    cout << endl;
  }
}

void Graph::PrintWithWeight() {
  cout << "ADJLIST:" << endl << endl;
  for (int i = 0; i < qt_vertex_; i++) {
    cout << "[" << adj_list_[i][0].number_ << "]";
    for (int x = 1; x < adj_list_[i].size(); x++) {
      cout  << "->" << adj_list_[i][x].weight_
            << "->" << "[" << adj_list_[i][x].number_
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
    cout << "[" << adj_list_[i][0].number_ << "]";
    for (int x = 1; x < adj_list_[i].size(); x++) {
      cout  << "->" << adj_list_[i][x].cost_
            << "->" << "[" << adj_list_[i][x].number_
            << "] ";
    }
    cout << endl;
  }
}

void Graph::PrintWithIncCost() {
  cout << endl << endl << "ADJLIST:" << endl << endl;
  for (int i = 0; i < qt_vertex_; i++) {
    cout << "[" << adj_list_[i][0].number_ << "]";
    for (int x = 1; x < adj_list_[i].size(); x++) {
      cout  << "->" << adj_list_[i][x].inc_cost_
            << "->" << "[" << adj_list_[i][x].number_
            << "] ";
    }
    cout << endl;
  }
}

void Graph::PrintWithQtRequests() {
  cout << endl << endl << "ADJLIST:" << endl << endl;
  for (int i = 0; i < qt_vertex_; i++) {
    cout << "[" << adj_list_[i][0].number_ << "]";
    for (int x = 1; x < adj_list_[i].size(); x++) {
      cout  << "->" << adj_list_[i][x].qt_requests_
            << "->" << "[" << adj_list_[i][x].number_
            << "]";
      if(adj_list_[i][x].qt_requests_ > 800) {
        cout << "Extrapolado o limite de comprimentos de onda da fibra " <<
             i << " - " << x << " - Quantidade de comprimentos de onda:" <<
             adj_list_[i][x].qt_requests_ << endl;
        system("PAUSE");
      }
    }
    cout << endl;
  }
}
