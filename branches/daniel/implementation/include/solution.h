// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#ifndef _PIFRO2_INCLUDE_SOLUTION_H_
#define _PIFRO2_INCLUDE_SOLUTION_H_

#include <vector>

#include "./macros.h"

class Solution
{
  public:

    double cost_;
    std::vector< std::pair< double, int > > ranking_;

    Solution();
    virtual ~Solution();
};

#endif // _PIFRO2_INCLUDE_SOLUTION_H_
