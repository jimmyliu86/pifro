// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#include "./vertex.h"

Vertex::Vertex() {
  number_ = -1;
  visited_ = -1;
  weight_ = 0;
  color_ = -1;
  level_ = -1;
  cost_ = 0;
  inc_cost_ = 0;
  qt_requests_ = 0;
}

Vertex::Vertex(int number, int visited, float weight) {
  number_ = number;
  visited_ = visited;
  weight_ = weight;
  color_ = -1;
  level_ = -1;
  cost_ = 0;
  inc_cost_ = 0;
  qt_requests_ = 0;
}

Vertex::~Vertex() {
}

void Vertex::SetProperties(int number, int visited, float weight) {
  number_ = number;
  visited_ = visited;
  weight_ = weight;
}

void Vertex::Print() {
  cout << "Vertex Data" << endl;
  cout << "Vertex Number: " << number_ << endl;
  cout << "Vertex Visited: " << visited_ << endl;
  cout << "Vertex Weight: " << weight_ << endl;
}
