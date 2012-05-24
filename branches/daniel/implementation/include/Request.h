// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#ifndef _PIFRO2_INCLUDE_REQUEST_H_
#define _PIFRO2_INCLUDE_REQUEST_H_

#include "./macros.h"

class Request {
  public:
    int src_, dst_, qt_roadm_, qt_, id_;
    float distance_, key_;

    Request();
    Request(int src, int dst, int qthops, int distance, int qt);
};

#endif  // _PIFRO2_INCLUDE_REQUEST_H_
