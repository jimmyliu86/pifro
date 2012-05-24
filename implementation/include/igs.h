// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#ifndef _PIFRO2_INCLUDE_IGS_H_
#define _PIFRO2_INCLUDE_IGS_H_

#include <time.h>

#include "./greedy.h"

class IGS {
  public:
    IGS();
    virtual ~IGS();
    float execute(Graph graph, Demand demand, int execution_time);
  private:
    float min_cost_;
};

#endif  // _PIFRO2_INCLUDE_IGS_H_
