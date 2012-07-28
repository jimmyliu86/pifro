// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#ifndef _PIFRO2_INCLUDE_MSPSC_H_
#define _PIFRO2_INCLUDE_MSPSC_H_

#include <float.h>

#include "./psc.h"

class MSPSC
{
  public:
    float min_cost_;

    MSPSC();
    float execute(Graph graph, Demand demand, int execution_time);
};

#endif // _PIFRO2_INCLUDE_MSPSC_H_
