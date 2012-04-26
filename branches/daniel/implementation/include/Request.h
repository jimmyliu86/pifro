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
    explicit Request(int src, int dst, int qthops, int distance, int qt);
    int GetSrc();
    int GetDst();
    int GetQtROADM();
    float GetDistance();
    int GetQt();
    float GetKey();
    int GetId();
    void SetSrc(int src);
    void SetDst(int dst);
    void SetQtROADM(int qtroadm);
    void SetDistance(float distance);
    void SetQt(int qt);
    void SetKey(float key);
    void SetId(int id);

  private:
};
#endif  // _PIFRO2_INCLUDE_REQUEST_H_
