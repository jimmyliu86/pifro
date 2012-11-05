// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#ifndef _PIFRO2_INCLUDE_DIFFERENTIALEVOLUTION_H_
#define _PIFRO2_INCLUDE_DIFFERENTIALEVOLUTION_H_

#include <time.h>
#include <algorithm>
#include <list>
#include <vector>
#include <float.h>

#include "./Graph.h"
#include "./Request.h"
#include "./Greedy.h"
#include "./psc.h"
#include "./solution.h"

class DifferentialEvolution
{
  public:
    Demand demand_;
    Graph graph_;
    time_t t_start_, t_stop_;
    int tex_, heuristic_, d_, np_, cr_, f_, mutation_type_, qt_pond_, cross_type_, best_, prev_best_;
    double min_cost_;
    std::vector<Solution> solutions_;

    explicit DifferentialEvolution(Graph graph, Demand demand, time_t t_start, int tex, int heuristic, int d, int np, int cr, int f, int mutation_type, int qt_pond, int cross_type);
    virtual ~DifferentialEvolution();

    void createInitialPopulation();
    float evolve();
};

#endif // _PIFRO2_INCLUDE_DIFFERENTIALEVOLUTION_H_
