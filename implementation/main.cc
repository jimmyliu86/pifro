// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#include <dirent.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <fstream>

#include "./vertex.h"
#include "./graph.h"
#include "./demand.h"
#include "./dijkstra.h"
#include "./greedy.h"
#include "./rvgs.h"
#include "./MTRand.h"
#include "./BRKGA.h"
#include "./BRKGADecoder.h"
#include "./igs.h"

using std::cin;
using std::stringstream;
using std::string;

int main(int argc, char *argv[]) {
  srand(time(NULL));

  cout.precision(50);
  int qt_executions = 5, delay_time = 0, time_for_execution_original = 600,
      order = 1;
  time_t TStart, TStop;
  string instance_folder = "F:/Instance/";
  string instance_out = "F:/Instance/OUTPUTS/Tab_Fernanda6/";

  std::vector<string> instances;
  instances.push_back("abilene"); // n
  instances.push_back("atlanta"); // n
  instances.push_back("cost266");
  instances.push_back("dfn-bwin"); // n
  instances.push_back("dfn-gwin"); // n
  instances.push_back("di-yuan"); // n
  instances.push_back("france");
  instances.push_back("geant"); // n
  instances.push_back("germany50");
  instances.push_back("giul39");
  instances.push_back("janos-us");
  instances.push_back("janos-us-ca");
  instances.push_back("newyork"); // n
  instances.push_back("nobel-eu");
  instances.push_back("nobel-germany");
  instances.push_back("nobel-us"); // n
  instances.push_back("norway");
  instances.push_back("pdh"); // n
  instances.push_back("pioro40");
  instances.push_back("polska"); // n
  instances.push_back("sun");
  instances.push_back("ta1");
  instances.push_back("ta2");
  instances.push_back("zib54");

  for (int f = 0; f < instances.size(); f++) {
    string output(instance_out + instances[f] + ".txt");
    string net_name_str(instance_folder +
                        instances[f] + "/" + instances[f] + ".net");
    string dem_name_str(instance_folder +
                        instances[f] + "/" + instances[f] + ".trf");

    char * net_name = new char[net_name_str.size() + 1];
    strcpy(net_name, net_name_str.c_str());

    char * dem_name = new char[dem_name_str.size() + 1];
    strcpy(dem_name, dem_name_str.c_str());

    ofstream fout(output.c_str());
    fout.precision(150);

    Graph g(net_name, 0);
    Demand d(dem_name, 0);

    // GREEDY
    fout << "GREEDY;BRKGA;IGS;" << endl;
    for (int j = 0; j < qt_executions; j++) {
      cout << "Starting GREEDY execution " <<
           j << " for '" << net_name << "'\n";
      // TStart = time(NULL);
      g.CleanCosts();
      d.Sort();
      Greedy greedy(g, d);
      // greedy.Execute(true, false);
      TStart = time(NULL);
      fout << (greedy.ExecuteWithRefine(true, false, TStart, time_for_execution_original) / order) << ";";
      cout << "Greedy execution " << j
           << " for " << "'" << net_name << "' finished at " << (time(NULL) - TStart) << " seconds " << endl;
      Sleep(delay_time);
      cout << "Finishing Greedy for '" << net_name << "'\n\n";

      // BRKGA
      int  curtime = 0;
      cout << "Starting BRKGA execution " << j << " for '" << net_name << "'\n";
      TStart = time(NULL);

      g.CleanCosts();
      d.Sort();

      // size of chromosomes
      const unsigned n = d.qt_request_;
      // size of population
      const unsigned p = g.qt_vertex_;
      // fraction of population to be the elite-set
      const double pe = 0.25;
      // fraction of population to be replaced by mutants
      const double pm = 0.05;
      // probability that offspring inherit an allele from elite parent
      const double rhoe = 0.70;
      // number of independent populations
      const unsigned K = 1;
      // number of threads for parallel decoding
      const unsigned MAXT = 1;

      // initialize the decoder
      BRKGADecoder decoder(g, d, TStart, time_for_execution_original);

      // seed to the random number generator
      const float rngSeed =
        (static_cast<float>(Uniform(0, 1)) / rand());
      // initialize the random number generator
      MTRand rng(rngSeed);

      // initialize the BRKGA-based heuristic
      int i = 1;

      BRKGA< BRKGADecoder, MTRand >
      algorithm(n, p, pe, pm, rhoe, decoder, rng, K, MAXT);

      /*BRKGA< BRKGADecoder, MTRand >
      algorithm(n, p, pe, pm, rhoe, TStart, decoder, rng, K, MAXT);*/

      // TEMPO DE EXECUÇÃO EM SEGUNDOS {DANIEL}
      //algorithm.tex = time_for_execution_original;

      // current generation
      unsigned generation = 0;
      // exchange best individuals at every 100 generations
      const unsigned X_INTVL = 100;
      // exchange top 2 best
      const unsigned X_NUMBER = 2;
      // run for 1000 gens
      // const unsigned MAX_GENS = 1000;
      const unsigned MAX_GENS = 1000;

      do {
        TStop = time(NULL);
        curtime = TStop - TStart;
        if(curtime < time_for_execution_original) {
          algorithm.evolve();
          if ( (++generation) % X_INTVL == 0 ) {
            // exchange top individuals
            algorithm.exchangeElite(X_NUMBER);
          }

          time_t TStop = time(NULL);
          curtime = TStop - TStart;
          i++;
        } else {
          break;
        }
      } while ((generation < MAX_GENS) && (curtime < time_for_execution_original));

      fout << (algorithm.getBestFitness() / order) << ";";
      cout << "BRKGA execution " << j
           << " for " << "'" << net_name << "' finished at " << curtime << " seconds" << endl;
      Sleep(delay_time);
      cout << "Finishing BRKGA for '" << net_name << "'\n\n";

      // IGS
      // time_for_execution = curtime;
      cout << "Starting IGS execution " << j << " for '" << net_name << "'\n";

      TStart = time(NULL);
      g.CleanCosts();
      d.Sort();
      IGS igs;
      fout << (igs.execute(g, d, time_for_execution_original) / order) << ";\n";
      cout << "IGS execution " << j
           << " for " << "'" << net_name << "' finished at " << (time(NULL) - TStart) << " seconds" << endl;
      cout << "Finishing IGS for '" << net_name << "'\n\n";
      Sleep(delay_time);
    }

    fout.close();
  }
  system("PAUSE");
  return 0;
}
