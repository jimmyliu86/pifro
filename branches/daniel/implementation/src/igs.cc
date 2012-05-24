// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#include "./igs.h"

IGS::IGS() {
}

IGS::~IGS() {
}

float IGS::execute(Graph graph, Demand demand, int execution_time) {
  time_t t_start = time(NULL);
  int k =  (demand.vec_request_.size() * 0.25);
  float act = 0, beta = 0;

  Greedy s(graph, demand);
  s.Execute(true, false);
  s.ExecuteWithRefine(false, false);

  Greedy s_star = s;

  time_t t_stop = time(NULL);

  while ((t_stop - t_start) < execution_time) {
    Greedy s2 = s;
    s2.ExecuteWithRefine(k);
    s2.ExecuteWithRefine(false, false);

    if (s2.min_cost_ <= ((1 + beta) * s_star.min_cost_)) {
      s = s2;
    }

    if (s.min_cost_ < s_star.min_cost_) {
      s_star = s;
    }
    t_stop = time(NULL);
  }

  min_cost_ = s_star.min_cost_;
  return min_cost_;
}
