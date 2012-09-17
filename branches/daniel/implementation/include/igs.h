// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#ifndef _PIFRO2_INCLUDE_IGS_H_
#define _PIFRO2_INCLUDE_IGS_H_

#include <time.h>

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

#include "./greedy.h"
#include "./psc.h"

class IGS {
  public:
    IGS();
    virtual ~IGS();
    float executeWithGreedyMinor(Graph graph, Demand demand, int execution_time, double k, double beta, bool roulete);
    float executeWithPSCMinor(Graph graph, Demand demand, int execution_time, double k, double beta, bool roulete);
    float executeWithGreedyMinorEqual(Graph graph, Demand demand, int execution_time, double k, double beta, bool roulete);
    float executeWithPSCMinorEqual(Graph graph, Demand demand, int execution_time, double k, double beta, bool roulete);
    float executeWithGreedyMinorX(Graph graph, Demand demand, int execution_time, double k, double beta, int x, bool roulete);
    float executeWithPSCMinorX(Graph graph, Demand demand, int execution_time, double k, double beta, int x, bool roulete);
    float executeWithGreedyMinorEqualX(Graph graph, Demand demand, int execution_time, double k, double beta, int x, bool roulete);
    float executeWithPSCMinorEqualX(Graph graph, Demand demand, int execution_time, double k, double beta, int x, bool roulete);
    int rouletespin(Demand demand);
  private:
    float min_cost_;
};

#endif  // _PIFRO2_INCLUDE_IGS_H_
