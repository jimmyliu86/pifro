// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#ifndef _PIFRO2_INCLUDE_BREADTHFIRST_H_
#define _PIFRO2_INCLUDE_BREADTHFIRST_H_

#include <queue>
#include <vector>
#include <iostream>

#include "./macros.h"
#include "./vertex.h"

using std::cout;
using std::endl;

class BreadthFirst {
  public:
    BreadthFirst();
    float GetKmDistance();
    std::vector<int> GetWay();
    void SetKmDistance(float kmdistance);
    void SetWay(std::vector<int> way);
    int GetQtROADM(std::vector<Vertex>*& adjlist,
                   int src,
                   int dst,
                   int qtvertex);
    float CalculateDistance(int src,
                            int dst,
                            std::vector<Vertex>*& adjlist);

    float SetCostOfWay(int src,
                       int dst,
                       std::vector<Vertex>*& adjlist);
    void PrintWay();
  private:
    float km_distance_;
    std::vector<int> way_;
};

#endif  // _PIFRO2_INCLUDE_BREADTHFIRST_H_
