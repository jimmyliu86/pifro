// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#include "./functions.h"

Functions::Functions() {
}

Functions::~Functions() {
}

float Functions::Fwdm(int w, float l) {
  float fret = 0, c1 = 0, c2 = 0, c3 = 0;
  c1 = 2 * ROADMCost;
  c2 = (1 / LOA) * OACost;
  c3 = (1 / LOT) * 2 * OTCost;
  fret = c1 * ceil(w / U) + c2 * l * ceil(w / U) + c3 * w * l;
  return fret;
}
