// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#ifndef _PIFRO2_INCLUDE_DEMAND_H_
#define _PIFRO2_INCLUDE_DEMAND_H_

#include <time.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

#include "./macros.h"
#include "./request.h"
#include "./graph.h"
#include "./comparision.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::fstream;
using std::string;

class Demand {
  public:
    std::vector<Request> vec_request_;
    int qt_request_, qt_wavelength_, qt_paths_;
    std::vector< std::vector<int> >paths_;

    Demand();
    explicit Demand(char* filename,
                    int tipo);
    void LoadSolutionFromPATHFile(char* filename);
    void LoadSolutionFromSOLFile(char* filename);

    void Sort();
    void Print(string output);
};

#endif  // _PIFRO2_INCLUDE_DEMAND_H_
