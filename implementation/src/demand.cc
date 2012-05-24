// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#include <vector>

#include "./demand.h"

Demand::Demand() {
}

Demand::Demand(char* filename,
               int tipo) {
  if (tipo == 0) {
    LoadFromTRFFile(filename);
  }
}

void Demand::LoadFromTRFFile(char* filename) {
  ifstream fin(filename);
  fin >> qt_request_;
  Request request;
  int src, dst;
  int qt;

  for (int i = 0; i < qt_request_; i++) {
    fin >> src;
    fin >> dst;
    fin >> qt;

    request.src_ = src;
    request.dst_ = dst;
    request.qt_ = qt;
    request.id_ = i;

    vec_request_.push_back(request);
  }
  fin.close();
}

void Demand::Sort() {
  srand(time(NULL));
  for (int i = 0; i < vec_request_.size(); i++) {
    vec_request_[i].key_ = ((static_cast<float>(Uniform(0, 1)) / rand()));
  }
  sort(vec_request_.begin(), vec_request_.end(), comparision_request_by_key());
}

void Demand::Print() {
  for (int i = 0; i < vec_request_.size(); i++) {
    cout << "Source: " << vec_request_[i].src_
         << " - Destination: " << vec_request_[i].dst_
         << " - Quantity: " << vec_request_[i].qt_
         << " - QtROADM: " << vec_request_[i].qt_roadm_
         << endl;
  }
}
