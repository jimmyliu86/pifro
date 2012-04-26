// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#ifndef _PIFRO2_INCLUDE_COMPARISION_H_
#define _PIFRO2_INCLUDE_COMPARISION_H_


struct comparision_request_by_qtroadm {
  public:
    bool operator()(Request a, Request b) {
      return a.GetQtROADM() < b.GetQtROADM();
  }
};


struct comparision_request_by_key {
  public:
    bool operator()(Request a, Request b) {
      return a.GetKey() < b.GetKey();
  }
};

#endif  // _PIFRO2_INCLUDE_COMPARISION_H_