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

int Vertex::GetNumber() {
  return number_;
}

int Vertex::GetVisited() {
  return visited_;
}

float Vertex::GetWeight() {
  return weight_;
}

int Vertex::GetColor() {
  return color_;
}

int Vertex::GetLevel() {
  return level_;
}

int Vertex::GetPrevious() {
  return previous_;
}

float Vertex::GetCost() {
  return cost_;
}

float Vertex::GetIncCost() {
  return inc_cost_;
}

bool Vertex::GetEnabled() {
  return enabled_;
}

int Vertex::GetQtRequests() {
  return qt_requests_;
}

void Vertex::SetNumber(int number) {
  number_ = number;
}

void Vertex::SetVisited(int visited) {
  visited_ = visited;
}

void Vertex::SetWeight(float weight) {
  weight_ = weight;
}

void Vertex::SetColor(int color) {
  color_ = color;
}

void Vertex::SetLevel(int level) {
  level_ = level;
}

void Vertex::SetProperties(int number, int visited, float weight) {
  number_ = number;
  visited_ = visited;
  weight_ = weight;
}

void Vertex::SetPrevious(int previous) {
  previous_ = previous;
}

void Vertex::SetCost(float cost) {
  cost_ = cost;
}

void Vertex::SetIncCost(float inccost) {
  inc_cost_ = inccost;
}

void Vertex::SetEnabled(bool enabled) {
  enabled_ = enabled;
}

void Vertex::SetQtRequests(int qtrequests) {
  qt_requests_ = qtrequests;
}

void Vertex::Print() {
  cout << "Vertex Data" << endl;
  cout << "Vertex Number: " << GetNumber() << endl;
  cout << "Vertex Visited: " << GetVisited() << endl;
  cout << "Vertex Weight: " << GetWeight() << endl;
}
