// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#include "vns.h"

VNS::VNS() {
}

VNS::~VNS() {
}

float VNS::executeWithGreedyMinor(Graph graph, Demand demand, int execution_time, double beta, double mink, double maxk, double inck, int qtit) {
  time_t t_start = time(NULL);
  double x = mink;
  int it = 0;
  float act = 0, beta_ = beta;

  Greedy s(graph, demand);
  s.ExecuteWithRefine(true, true, t_start, execution_time);

  Greedy s_star = s;

  time_t t_stop = time(NULL);

  while ((t_stop - t_start) < execution_time) {
    Greedy s2 = s;
    int l = (demand.vec_request_.size() * x);
    s2.ExecuteWithRefine(demand.vec_request_.size() * x, t_start, execution_time, true);
    s2.ExecuteWithRefine(false, false, t_start, execution_time);
    if (s2.min_cost_ < ((1 + beta_) * s_star.min_cost_)) {
      s = s2;
    }else{
      if(it >= qtit){
        x = x + inck;
        it = 0;
      }
      if(x > maxk){
        x = mink;
        s.ExecuteWithRefine(true, true, t_start, execution_time);
      }
    }

    if (s.min_cost_ < s_star.min_cost_) {
      s_star = s;
    }
    t_stop = time(NULL);
    it++;
  }

  min_cost_ = s_star.min_cost_;
  return min_cost_;
}

float VNS::executeWithGreedyMinorEqual(Graph graph, Demand demand, int execution_time, double mink, double maxk, double inck, int qtit) {
  time_t t_start = time(NULL);
  int x = mink, it = 0;
  float act = 0;

  Greedy s(graph, demand);
  s.ExecuteWithRefine(true, true, t_start, execution_time);

  Greedy s_star = s;

  time_t t_stop = time(NULL);

  while ((t_stop - t_start) < execution_time) {
    Greedy s2 = s;
    s2.ExecuteWithRefine(demand.vec_request_.size() * x, t_start, execution_time, true);
    s2.ExecuteWithRefine(false, false, t_start, execution_time);

    if (s2.min_cost_ <= s_star.min_cost_) {
      s = s2;
    }else{
      if(it >= qtit){
        x = x + inck;
        it = 0;
      }
      if(x > maxk){
        x = mink;
        s.ExecuteWithRefine(true, true, t_start, execution_time);
      }
    }

    if (s.min_cost_ < s_star.min_cost_) {
      s_star = s;
    }
    t_stop = time(NULL);
    it++;
  }

  min_cost_ = s_star.min_cost_;
  return min_cost_;
}

float VNS::executeWithPSCMinor(Graph graph, Demand demand, int execution_time, double beta, double mink, double maxk, double inck, int qtit) {
  time_t t_start = time(NULL);
  int x = mink, it = 0;
  float act = 0, beta_ = beta;

  PSC s(graph, demand);
  s.ExecuteWithRefine(true, true, t_start, execution_time);

  PSC s_star = s;

  time_t t_stop = time(NULL);

  while ((t_stop - t_start) < execution_time) {
    PSC s2 = s;
    s2.ExecuteWithRefine(demand.vec_request_.size() * x, t_start, execution_time, true);
    s2.ExecuteWithRefine(false, false, t_start, execution_time);

    if (s2.min_cost_ < ((1 + beta_) * s_star.min_cost_)) {
      s = s2;
    }else{
      if(it >= qtit){
        x = x + inck;
        it = 0;
      }
      if(x > maxk){
        x = mink;
        s.ExecuteWithRefine(true, true, t_start, execution_time);
      }
    }

    if (s.min_cost_ < s_star.min_cost_) {
      s_star = s;
    }
    t_stop = time(NULL);
    it++;
  }

  min_cost_ = s_star.min_cost_;
  return min_cost_;
}

float VNS::executeWithPSCMinorEqual(Graph graph, Demand demand, int execution_time, double mink, double maxk, double inck, int qtit) {
  time_t t_start = time(NULL);
  int x = mink, it = 0;
  float act = 0;

  PSC s(graph, demand);
  s.ExecuteWithRefine(true, true, t_start, execution_time);

  PSC s_star = s;

  time_t t_stop = time(NULL);

  while ((t_stop - t_start) < execution_time) {
    PSC s2 = s;
    s2.ExecuteWithRefine(x, t_start, execution_time, true);
    s2.ExecuteWithRefine(false, false, t_start, execution_time);

    if (s2.min_cost_ <= s_star.min_cost_) {
      s = s2;
    }else{
      if(it >= qtit){
        x = x + inck;
        it = 0;
      }
      if(x > maxk){
        x = mink;
        s.ExecuteWithRefine(true, true, t_start, execution_time);
      }
    }

    if (s.min_cost_ < s_star.min_cost_) {
      s_star = s;
    }
    t_stop = time(NULL);
    it++;
  }

  min_cost_ = s_star.min_cost_;
  return min_cost_;
}
