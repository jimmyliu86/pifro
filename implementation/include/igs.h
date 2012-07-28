// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#ifndef _PIFRO2_INCLUDE_IGS_H_
#define _PIFRO2_INCLUDE_IGS_H_

#include <time.h>

#include "./greedy.h"
#include "./psc.h"

class IGS {
  public:
    IGS();
    virtual ~IGS();
    float executeWithGreedyMinor(Graph graph, Demand demand, int execution_time, double k, double beta);
    float executeWithPSCMinor(Graph graph, Demand demand, int execution_time, double k, double beta);
    float executeWithGreedyMinorEqual(Graph graph, Demand demand, int execution_time, double k, double beta);
    float executeWithPSCMinorEqual(Graph graph, Demand demand, int execution_time, double k, double beta);
    float executeWithGreedyMinorX(Graph graph, Demand demand, int execution_time, double k, double beta, int x);
    float executeWithPSCMinorX(Graph graph, Demand demand, int execution_time, double k, double beta, int x);
    float executeWithGreedyMinorEqualX(Graph graph, Demand demand, int execution_time, double k, double beta, int x);
    float executeWithPSCMinorEqualX(Graph graph, Demand demand, int execution_time, double k, double beta, int x);
  private:
    float min_cost_;
};

#endif  // _PIFRO2_INCLUDE_IGS_H_
