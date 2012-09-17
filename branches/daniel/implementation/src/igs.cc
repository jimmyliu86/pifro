// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#include "./igs.h"

IGS::IGS() {
}

IGS::~IGS() {
}

float IGS::executeWithGreedyMinor(Graph graph, Demand demand, int execution_time, double k, double beta, bool roulete) {
  time_t t_start = time(NULL);
  int k_ = (demand.vec_request_.size() * k), x = 0;
  float act = 0, beta_ = beta;

  Greedy s(graph, demand);
  s.ExecuteWithRefine(true, true, t_start, execution_time);

  Greedy s_star = s;

  time_t t_stop = time(NULL);

  while ((t_stop - t_start) < execution_time) {
    Greedy s2 = s;
    s2.ExecuteWithRefine(k_, t_start, execution_time, roulete);
    s2.ExecuteWithRefine(false, false, t_start, execution_time);

    if (s2.min_cost_ < ((1 + beta_) * s_star.min_cost_)) {
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

float IGS::executeWithGreedyMinorEqual(Graph graph, Demand demand, int execution_time, double k, double beta, bool roulete) {
  time_t t_start = time(NULL);
  int k_ = (demand.vec_request_.size() * k), x = 0;
  float act = 0, beta_ = beta;

  Greedy s(graph, demand);
  s.ExecuteWithRefine(true, true, t_start, execution_time);

  Greedy s_star = s;

  time_t t_stop = time(NULL);

  while ((t_stop - t_start) < execution_time) {
    Greedy s2 = s;
    s2.ExecuteWithRefine(k_, t_start, execution_time, roulete);
    s2.ExecuteWithRefine(false, false, t_start, execution_time);

    if (s2.min_cost_ <= ((1 + beta_) * s_star.min_cost_)) {
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

float IGS::executeWithGreedyMinorX(Graph graph, Demand demand, int execution_time, double k, double beta, int x, bool roulete) {
  time_t t_start = time(NULL);
  int k_ = (demand.vec_request_.size() * k), x_ = 0;
  float act = 0, beta_ = beta;

  Greedy s(graph, demand);
  s.ExecuteWithRefine(true, true, t_start, execution_time);

  Greedy s_star = s;

  time_t t_stop = time(NULL);

  while ((t_stop - t_start) < execution_time) {
    Greedy s2 = s;
    s2.ExecuteWithRefine(k_, t_start, execution_time, roulete);
    s2.ExecuteWithRefine(false, false, t_start, execution_time);

    if (s2.min_cost_ < ((1 + beta_) * s_star.min_cost_)) {
      s = s2;
    }

    if (s.min_cost_ < s_star.min_cost_) {
      s_star = s;
      x_ = 0;
    }
    // X iteracoes sem melhora, recria-se s
    else{
      x_++;
      if(x_ >= x){
        s.graph_ = graph;
        s.demand_ = demand;
        s.ExecuteWithRefine(true, true, t_start, execution_time);
        x_ = 0;
      }
    }

    t_stop = time(NULL);
  }

  min_cost_ = s_star.min_cost_;
  return min_cost_;
}

float IGS::executeWithGreedyMinorEqualX(Graph graph, Demand demand, int execution_time, double k, double beta, int x, bool roulete) {
  time_t t_start = time(NULL);
  int k_ = (demand.vec_request_.size() * k), x_ = 0;
  float act = 0, beta_ = beta;

  Greedy s(graph, demand);
  s.ExecuteWithRefine(true, true, t_start, execution_time);

  Greedy s_star = s;

  time_t t_stop = time(NULL);

  while ((t_stop - t_start) < execution_time) {
    Greedy s2 = s;
    s2.ExecuteWithRefine(k_, t_start, execution_time, roulete);
    s2.ExecuteWithRefine(false, false, t_start, execution_time);

    if (s2.min_cost_ < ((1 + beta_) * s_star.min_cost_)) {
      s = s2;
    }

    if (s.min_cost_ < s_star.min_cost_) {
      s_star = s;
      x_ = 0;
    }
    // X iteracoes sem melhora, recria-se s
    else{
      x_++;
      if(x_ >= x){
        s.graph_ = graph;
        s.demand_ = demand;
        s.ExecuteWithRefine(true, true, t_start, execution_time);
        x_ = 0;
      }
    }

    t_stop = time(NULL);
  }

  min_cost_ = s_star.min_cost_;
  return min_cost_;
}



float IGS::executeWithPSCMinor(Graph graph, Demand demand, int execution_time, double k, double beta, bool roulete) {
  time_t t_start = time(NULL);
  int k_ = (demand.vec_request_.size() * k), x = 0;
  float act = 0, beta_ = beta;

  PSC s(graph, demand);
  s.ExecuteWithRefine(true, true, t_start, execution_time);

  PSC s_star = s;

  time_t t_stop = time(NULL);

  while ((t_stop - t_start) < execution_time) {
    PSC s2 = s;
    s2.ExecuteWithRefine(k_, t_start, execution_time, roulete);
    s2.ExecuteWithRefine(false, false, t_start, execution_time);

    if (s2.min_cost_ < ((1 + beta_) * s_star.min_cost_)) {
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

float IGS::executeWithPSCMinorEqual(Graph graph, Demand demand, int execution_time, double k, double beta, bool roulete) {
  time_t t_start = time(NULL);
  int k_ = (demand.vec_request_.size() * k), x = 0;
  float act = 0, beta_ = beta;

  PSC s(graph, demand);
  s.ExecuteWithRefine(true, true, t_start, execution_time);

  PSC s_star = s;

  time_t t_stop = time(NULL);

  while ((t_stop - t_start) < execution_time) {
    PSC s2 = s;
    s2.ExecuteWithRefine(k_, t_start, execution_time, roulete);
    s2.ExecuteWithRefine(false, false, t_start, execution_time);

    if (s2.min_cost_ <= ((1 + beta_) * s_star.min_cost_)) {
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

float IGS::executeWithPSCMinorX(Graph graph, Demand demand, int execution_time, double k, double beta, int x, bool roulete) {
  time_t t_start = time(NULL);
  int k_ = (demand.vec_request_.size() * k), x_ = 0;
  float act = 0, beta_ = beta;

  PSC s(graph, demand);
  s.ExecuteWithRefine(true, true, t_start, execution_time);

  PSC s_star = s;

  time_t t_stop = time(NULL);

  while ((t_stop - t_start) < execution_time) {
    PSC s2 = s;
    s2.ExecuteWithRefine(k_, t_start, execution_time, roulete);
    s2.ExecuteWithRefine(false, false, t_start, execution_time);

    if (s2.min_cost_ < ((1 + beta_) * s_star.min_cost_)) {
      s = s2;
    }

    if (s.min_cost_ < s_star.min_cost_) {
      s_star = s;
      x_ = 0;
    }
    // X iteracoes sem melhora, recria-se s
    else{
      x_++;
      if(x_ >= x){
        s.graph_ = graph;
        s.demand_ = demand;
        s.ExecuteWithRefine(true, true, t_start, execution_time);
        x_ = 0;
      }
    }

    t_stop = time(NULL);
  }

  min_cost_ = s_star.min_cost_;
  return min_cost_;
}

float IGS::executeWithPSCMinorEqualX(Graph graph, Demand demand, int execution_time, double k, double beta, int x, bool roulete) {
  time_t t_start = time(NULL);
  int k_ = (demand.vec_request_.size() * k), x_ = 0;
  float act = 0, beta_ = beta;

  PSC s(graph, demand);
  s.ExecuteWithRefine(true, true, t_start, execution_time);

  PSC s_star = s;

  time_t t_stop = time(NULL);

  while ((t_stop - t_start) < execution_time) {
    PSC s2 = s;
    s2.ExecuteWithRefine(k_, t_start, execution_time, roulete);
    s2.ExecuteWithRefine(false, false, t_start, execution_time);

    if (s2.min_cost_ < ((1 + beta_) * s_star.min_cost_)) {
      s = s2;
    }

    if (s.min_cost_ < s_star.min_cost_) {
      s_star = s;
      x_ = 0;
    }
    // X iteracoes sem melhora, recria-se s
    else{
      x_++;
      if(x_ >= x){
        s.graph_ = graph;
        s.demand_ = demand;
        s.ExecuteWithRefine(true, true, t_start, execution_time);
        x_ = 0;
      }
    }

    t_stop = time(NULL);
  }

  min_cost_ = s_star.min_cost_;
  return min_cost_;
}
