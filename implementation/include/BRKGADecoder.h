// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#ifndef _PIFRO2_INCLUDE_BRKGADECODER_H_
#define _PIFRO2_INCLUDE_BRKGADECODER_H_

#include <time.h>
#include <algorithm>
#include <list>
#include <vector>
#include <float.h>

#include "./Graph.h"
#include "./Request.h"
#include "./Greedy.h"
#include "./psc.h"

class BRKGADecoder {
  public:
    Demand demand_;
    Graph graph_;

    explicit BRKGADecoder(Graph graph, Demand demand, time_t tstart, int tex, int heuristic);
    virtual ~BRKGADecoder();

    double decode(const std::vector< double >& chromosome) const;

  private:
    time_t TStart, TStop;
    int Tex, Heuristic;

};

#endif  // _PIFRO2_INCLUDE_BRKGADECODER_H_
