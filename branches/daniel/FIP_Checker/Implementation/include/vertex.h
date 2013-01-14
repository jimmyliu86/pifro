// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#ifndef _PIFRO2_INCLUDE_VERTEX_H_
#define _PIFRO2_INCLUDE_VERTEX_H_

#include <iostream>
#include <cstdlib>

#include "./macros.h"

using std::cout;
using std::endl;

class Vertex {
  public:
    int number_, visited_, color_, level_, previous_, qt_requests_;
    float weight_, cost_, inc_cost_;
    bool enabled_;

    Vertex();
    Vertex(int number, int visited, float weight);
    ~Vertex();
    void SetProperties(int number, int visited, float weight);
    void Print();
};

#endif  // _PIFRO2_INCLUDE_VERTEX_H_
