// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#ifndef _PIFRO2_INCLUDE_BREADTHFIRST_H_
#define _PIFRO2_INCLUDE_BREADTHFIRST_H_

#include <queue>
#include <vector>
#include <iostream>

#include "./Macros.h"
#include "./Vertex.h"

using std::cout;
using std::endl;

class BreadthFirst {
  public:
    BreadthFirst();
    float getKmDistance();
    std::vector<int> getWay();
    void setKmDistance(float kmdistance);
    void setWay(std::vector<int> way);
    int getQtROADM(std::vector<Vertex>*& adjlist,
                   int src,
                   int dst,
                   int qtvertex);
    float calculateDistance(int src,
                            int dst,
                            std::vector<Vertex>*& adjlist);

    float setCostOfWay(int src,
                       int dst,
                       std::vector<Vertex>*& adjlist);
    void printWay();
  private:
    float KmDistance;
    std::vector<int> Way;
};

#endif  // _PIFRO2_INCLUDE_BREADTHFIRST_H_
