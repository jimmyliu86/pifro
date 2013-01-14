// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#include <vector>

#include "./demand.h"

Demand::Demand() {
}

Demand::Demand(char* filename,
               int tipo) {
  if (tipo == 0) {
    LoadSolutionFromSOLFile(filename);
  }
}

void Demand::LoadSolutionFromPATHFile(char* filename) {
  ifstream fin(filename);
  fin >> qt_paths_;
  /*Request request;
  int src, dst;
  int qt;
  qt_wavelength_ = 0;*/

  for (int i = 0; i < qt_paths_; i++) {
    char* aux = 0;
    int rep = 0;
    fin.getline(aux,9999);

    /*request.src_ = src;
    request.dst_ = dst;
    request.qt_ = qt;
    qt_wavelength_ += qt;
    request.id_ = i;

    vec_request_.push_back(request);*/
    int y = 0;
    while(aux[y] != '\n')
    {
      if(aux[y] == ' ') {
        rep++;
      }
      y++;
    }


    string tmp = "";
    int w = 0;
    for(int x = 0; x < rep; x++) {
      while(aux[w] != ' '){
        tmp += aux[w];
        w++;
      }
      w++;
      paths_[i].push_back(atoi(tmp.c_str()));
    }
  }
  fin.close();
}

void Demand::LoadSolutionFromSOLFile(char* filename) {
  ifstream fin(filename);
  fin >> qt_paths_;

  for (int i = 0; i < qt_paths_; i++){
      Request tmp;
      fin >> tmp.src_;
      fin >> tmp.dst_;
      fin >> tmp.qt_;
      vec_request_.push_back(tmp);
  }
  fin.close();
}

void Demand::Print(string output) {
  ofstream fout;
  fout.open(output.c_str(), fstream::app);
  fout.precision(150);
  fout << "\n\nDemand solution file: ";
  fout << endl;
  for (int i = 0; i < vec_request_.size(); i++) {
    fout << vec_request_[i].src_;
    fout << " - ";
    fout << vec_request_[i].dst_;
    fout << " - ";
    fout << vec_request_[i].qt_ ;
    fout << endl;
  }
  fout.close();
}
