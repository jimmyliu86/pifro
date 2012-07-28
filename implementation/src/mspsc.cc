// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#include "mspsc.h"

MSPSC::MSPSC()
{
  //ctor
}

float MSPSC::execute(Graph graph, Demand demand, int execution_time) {
  time_t t_start = time(NULL);
  time_t t_stop = time(NULL);

  min_cost_ =  FLT_MAX;

  PSC psc(graph, demand);
  while ((t_stop - t_start) < execution_time) {
    psc.ExecuteWithRefine(true, true, t_start, execution_time);

    cout << "MSPSC MIN COST: " << psc.min_cost_ << "\n";
    if(psc.min_cost_ < min_cost_){
      min_cost_ = psc.min_cost_;
    }

    t_stop = time(NULL);
  }

  return min_cost_;
}
