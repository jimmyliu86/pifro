// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#ifndef _PIFRO2_INCLUDE_BRKGADECODER_H_
#define _PIFRO2_INCLUDE_BRKGADECODER_H_

#include <time.h>
#include <algorithm>
#include <list>
#include <vector>

#include "./Graph.h"
#include "./Request.h"
#include "./Greedy.h"

class BRKGADecoder {
  public:
    explicit BRKGADecoder(Graph& graph, std::vector<Request>& vecrequest);
    virtual ~BRKGADecoder();

    double decode(const std::vector< double >& chromosome) const;

  private:
    std::vector<Request> vec_request_;
    Graph graph_;
};

#endif  // _PIFRO2_INCLUDE_BRKGADECODER_H_