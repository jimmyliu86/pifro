// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#include "./request.h"

Request::Request() {
  src_ = 0;
  dst_ = 0;
  qt_roadm_ = 0;
  distance_ = 0;
  qt_ = 0;
}


Request::Request(int src, int dst, int qtroadm, int distance, int qt) {
  src_ = src;
  dst_ = dst;
  qt_roadm_ = qtroadm;
  distance_ = distance;
  qt_ = qt;
}
