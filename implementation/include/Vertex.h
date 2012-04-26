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
    explicit Vertex();
    explicit Vertex(int number, int visited, float weight);
    ~Vertex();
    int GetNumber();
    int GetVisited();
    float GetWeight();
    int GetColor();
    int GetLevel();
    int GetPrevious();
    float GetCost();
    float GetIncCost();
    bool GetEnabled();
    int GetQtRequests();
    void SetNumber(int number);
    void SetVisited(int visited);
    void SetWeight(float weight);
    void SetColor(int color);
    void SetLevel(int level);
    void SetPrevious(int previous);
    void SetCost(float cost);
    void SetIncCost(float inccost);
    void SetEnabled(bool enabled);
    void SetQtRequests(int qtrequests);
    void SetProperties(int number, int visited, float weight);
    void Print();

  private:
    int number_, visited_, color_, level_, previous_, qt_requests_;
    float weight_, cost_, inc_cost_;
    bool enabled_;
};

#endif  // _PIFRO2_INCLUDE_VERTEX_H_
