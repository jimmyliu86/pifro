// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#ifndef _PIFRO2_INCLUDE_DEMAND_H_
#define _PIFRO2_INCLUDE_DEMAND_H_

#include <iostream>
#include <vector>

#include "./Macros.h"
#include "./Request.h"
#include "./Graph.h"
#include "./BreadthFirst.h"
#include "./Comparision.h"

using std::cout;
using std::endl;
using std::ifstream;


class Demand {
  public:
    Demand();
    explicit Demand(char* filename,
                    int tipo,
                    std::vector<Vertex>*& adjlist,
                    int qtvertex);
    std::vector<Request>& getVecRequest();
    void setVecRequest(std::vector<Request> vecrequest);
    int getQtRequest();
    void setQtRequest(int qtrequest);

    void loadFromTRFFile(char* filename,
                         std::vector<Vertex>*& adjlist,
                         int qtvertex);
    int qtROADMByBFS(std::vector<Vertex>*& adjlist,
                     int src,
                     int dst,
                     int qtvertex);
    void print();
  private:
    std::vector<Request> VecRequest;
    int QtRequest;
};

#endif  // _PIFRO2_INCLUDE_DEMAND_H_
