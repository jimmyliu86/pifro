// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#ifndef _PIFRO2_INCLUDE_CHECKER_H_
#define _PIFRO2_INCLUDE_CHECKER_H_

#include <vector>
#include <iostream>
#include <fstream>

#include "./macros.h"
#include "./vertex.h"
#include "./functions.h"
#include "./demand.h"
#include "./graph.h"

class Checker
{
  public:
    Functions functions_;

    Checker();
    virtual ~Checker();
    float MergeGraphAndDemand(Graph& graph, Demand& demand);
  protected:
  private:
};

#endif // _PIFRO2_INCLUDE_CHECKER_H
