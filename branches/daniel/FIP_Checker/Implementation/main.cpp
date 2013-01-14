// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <math.h>
#include <cmath>

#include "./graph.h"
#include "./demand.h"
#include "./checker.h"

using std::cin;
using std::stringstream;
using std::string;

int main(int argc, char *argv[]) {
  cout.precision(50);

  string instance_folder = "c:/FIP_Checker/instances/";
  string instance_out = "c:/FIP_Checker/Results/";

  std::vector<string> instances;
  instances.push_back("abilene");
  instances.push_back("atlanta");
  instances.push_back("cost266");
  instances.push_back("dfn-bwin");
  instances.push_back("dfn-gwin");
  instances.push_back("di-yuan");
  instances.push_back("france");
  instances.push_back("geant");
  instances.push_back("germany50");
  instances.push_back("giul39");
  instances.push_back("janos-us");
  instances.push_back("janos-us-ca");
  instances.push_back("newyork");
  instances.push_back("nobel-eu");
  instances.push_back("nobel-germany");
  instances.push_back("nobel-us");
  instances.push_back("norway");
  instances.push_back("pdh");
  instances.push_back("pioro40");
  instances.push_back("polska");
  instances.push_back("sun");
  instances.push_back("ta1");
  instances.push_back("ta2");
  instances.push_back("zib54");


  for (int f = 0; f < instances.size(); f++) {
    string output(instance_out + instances[f] + ".txt");
    string net_name_str(instance_folder +
                        instances[f] + "/" + instances[f] + ".net");
    string sol_name_str(instance_folder +
                         instances[f] + "/" + instances[f] + ".sol");

    char * net_name = new char[net_name_str.size() + 1];
    strcpy(net_name, net_name_str.c_str());

    char * dem_name = new char[sol_name_str.size() + 1];
    strcpy(dem_name, sol_name_str.c_str());

    ofstream fout(output.c_str());
    fout.precision(150);

    Graph g(net_name, 0);
    Demand d(dem_name, 0);

    Checker checker;
    checker.MergeGraphAndDemand(g, d);

    fout << "Solution verification for file: " << dem_name;
    fout << "\n\nSOLUTION COST: " << g.GetTotalCost();
    fout.close();
    g.PrintWithQtRequests(output);
    g.PrintWithCost(output);
    d.Print(output);

    cout << "Solution cost for " << instances[f] << ": " << g.GetTotalCost() << endl;

   }

  system("PAUSE");
  return 0;
}
