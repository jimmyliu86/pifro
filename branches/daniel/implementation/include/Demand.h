// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#ifndef _PIFRO2_INCLUDE_DEMAND_H_
#define _PIFRO2_INCLUDE_DEMAND_H_

#include <iostream>
#include <vector>

#include "./macros.h"
#include "./request.h"
#include "./graph.h"
#include "./breadth_first.h"
#include "./comparision.h"

using std::cout;
using std::endl;
using std::ifstream;


class Demand {
  public:
    Demand();
    explicit Demand(char* filename,
                    int tipo);
    std::vector<Request>& GetVecRequest();
    void SetVecRequest(std::vector<Request> vecrequest);
    int GetQtRequest();
    void SetQtRequest(int qtrequest);

    void LoadFromTRFFile(char* filename);
    int QtROADMByBFS(std::vector<Vertex>*& adjlist,
                     int src,
                     int dst,
                     int qtvertex);
    void Print();
  private:
    std::vector<Request> vec_request_;
    int qt_request_;
};

#endif  // _PIFRO2_INCLUDE_DEMAND_H_
