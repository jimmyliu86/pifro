// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#ifndef _PIFRO2_INCLUDE_FUNCTIONS_H_
#define _PIFRO2_INCLUDE_FUNCTIONS_H_

#include <math.h>
#include <cmath>

#include "./constants.h"

class Functions {
  public:
    Functions();
    ~Functions();
    float Fwdm(int w, float l);
    float F(float x);
    float F_line_wdm(int w, float l, int p);
  private:
};

#endif  // _PIFRO2_INCLUDE_FUNCTIONS_H_

