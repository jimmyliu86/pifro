// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#include <vector>

#include "./demand.h"

Demand::Demand() {
}

Demand::Demand(char* filename,
               int tipo,
               std::vector<Vertex>*& adjlist,
               int qtvertex) {
  if (tipo == 0) {
    LoadFromTRFFile(filename, adjlist, qtvertex);
  }
}

std::vector<Request>& Demand::GetVecRequest() {
  return vec_request_;
}

void Demand::SetVecRequest(std::vector<Request> vecrequest) {
  vec_request_ = vecrequest;
}

int Demand::GetQtRequest() {
  return qt_request_;
}

void Demand::SetQtRequest(int qtrequest) {
  qt_request_ = qtrequest;
}

// bool Demand::compare(Request request1, Request request2){
//     return (request1.getQtROADM() < request2.getQtROADM());
// }

void Demand::LoadFromTRFFile(char* filename,
                             std::vector<Vertex>*& adjlist,
                             int qtvertex) {
  ifstream fin(filename);
  fin >> qt_request_;
  Request request;
  int src, dst;
  int qt;

  // vector<int> visited;
  // BreadthFirst bfs;

  for (int i = 0; i < qt_request_; i++) {
    fin >> src;
    fin >> dst;
    fin >> qt;

    request.SetSrc(src);
    request.SetDst(dst);
    request.SetQt(qt);
    request.SetId(i);


    // request.setQtROADM(bfs.getQtROADM(adjlist, src, dst, qtvertex));
    // cout << "SRC: " << src << " - DST: " << dst
    // << " - QTROADM: " << request.getQtROADM() << endl;

    // ------>>> bfs.printWay();
    // cout << "======================================\n";
    // cout << "QTROADM: " << request.getQtROADM() << " - i: " << i << endl;
    vec_request_.push_back(request);
  }
  fin.close();

  // bfs.getQtROADM(adjlist, 5, 10, qtvertex);
  // bfs.printWay();
  // sort(VecRequest.begin(),
  //        VecRequest.end(),
  //        comparison_request_by_qtroadm());
  // cout << "QT: " << VecRequest.begin().getQtROADM()<<endl;
}

void Demand::Print() {
  for (int i = 0; i < vec_request_.size(); i++) {
    cout << "Source: " << vec_request_[i].GetSrc()
         << " - Destination: " << vec_request_[i].GetDst()
         << " - Quantity: " << vec_request_[i].GetQt()
         << " - QtROADM: " << vec_request_[i].GetQtROADM()
         << endl;
  }
}
