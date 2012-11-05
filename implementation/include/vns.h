// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#ifndef _PIFRO2_INCLUDE_VNS_H_
#define _PIFRO2_INCLUDE_VNS_H_

#include <time.h>

#include "./greedy.h"
#include "./psc.h"

class VNS {
  public:
    VNS();
    virtual ~VNS();
    float executeWithGreedyMinor(Graph graph, Demand demand, int execution_time, double beta, double mink, double maxk, double inck, int qtit);
    float executeWithPSCMinor(Graph graph, Demand demand, int execution_time, double beta, double mink, double maxk, double inck, int qtit);
    float executeWithGreedyMinorEqual(Graph graph, Demand demand, int execution_time, double mink, double maxk, double inck, int qtit);
    float executeWithPSCMinorEqual(Graph graph, Demand demand, int execution_time, double mink, double maxk, double inck, int qtit);
  private:
    float min_cost_;
};

#endif  // _PIFRO2_INCLUDE_VNS_H_
