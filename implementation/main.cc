// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#include <time.h>
#include <cstdlib>
#include <iostream>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <fstream>
#include <windows.h>

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
  // srand(time(NULL));
  cout.precision(50);
  int qt_executions = 5, delay_time = 5000, time_for_execution = 300 , order = 1000000;
  string instance_folder = "F:/Instance/";
  string instance_out = "F:/Instance/OUTPUTS/";

  std::vector<string> instances;
  instances.push_back("abilene");
  instances.push_back("atlanta");
  //instances.push_back("cost266");
  instances.push_back("dfn-bwin");
  instances.push_back("dfn-gwin");
  instances.push_back("di-yuan");
  //instances.push_back("france");
  instances.push_back("geant");
  //instances.push_back("germany50");
  //instances.push_back("giul39");
  //instances.push_back("janos-us");
  //instances.push_back("janos-us-ca");
  instances.push_back("newyork");
  //instances.push_back("nobel-eu");
  //instances.push_back("nobel-germany");
  instances.push_back("nobel-us");
  //instances.push_back("norway");
  instances.push_back("pdh");
  //instances.push_back("pioro40");
  instances.push_back("polska");
  //instances.push_back("sun");
  //instances.push_back("ta1");
  //instances.push_back("ta2");
  //instances.push_back("zib54");

  // Fazendo as heuristicas em todas as instancias que temos
  for(int f = 0; f < instances.size(); f++) {

    string output(instance_out + instances[f] + "_spolm.txt");
    string net_name_str(instance_folder + instances[f] + "/" + instances[f] + ".net");
    string dem_name_str(instance_folder + instances[f] + "/" + instances[f] + ".trf");

    char * net_name = new char[net_name_str.size() + 1];
    strcpy (net_name, net_name_str.c_str());

    char * dem_name = new char[dem_name_str.size() + 1];
    strcpy (dem_name, dem_name_str.c_str());

    ofstream fout(output.c_str());
    fout.precision(10);

    // GREEDY
    fout << "GREEDY SECTION" << endl;
    for(int j = 0; j < qt_executions; j++) {
      cout << "Starting GREEDY execution " << j << " for '" << net_name << "'\n";
      time_t TStart = time(NULL);
      Graph g(net_name, 0);
      Demand d(dem_name, 0);
      Greedy greedy(g, d);
      greedy.Execute(true, true);
      fout << (greedy.ExecuteWithRefine(true, true) / order) << ";\n";
      cout << "Greedy execution " << j << " for " << "'" << net_name << "' finished" << endl;
      Sleep(delay_time);
    }
    fout << endl;
    cout << "Finishing Greedy for '" << net_name << "'\n\n";

    // BRKGA
    fout << "BRKGA SECTION" << endl;
    for(int j = 0; j < qt_executions; j++) {
      cout << "Starting BRKGA execution " << j << " for '" << net_name << "'\n";
      time_t TStart = time(NULL);

      Graph g_brkga(net_name, 0);
      Demand d_brkga(dem_name, 0);
      //Greedy gr_brkga(g_brkga, d_brkga);
      //gr_brkga.Execute(true, false);

      // size of chromosomes
      const unsigned n = d_brkga.GetVecRequest().size();
      // const unsigned n = 100;
      // size of population
      // const unsigned p = 1000;
      // const unsigned p = 100;
      const unsigned p = d_brkga.GetVecRequest().size();
      // fraction of population to be the elite-set
      const double pe = 0.20;
      // fraction of population to be replaced by mutants
      const double pm = 0.10;
      // probability that offspring inherit an allele from elite parent
      const double rhoe = 0.70;
      // number of independent populations
      const unsigned K = 3;
      // number of threads for parallel decoding
      const unsigned MAXT = 2;

      // initialize the decoder
      BRKGADecoder decoder(g_brkga, d_brkga);

      // seed to the random number generator
      const float rngSeed = 0;
      //const float rngSeed = time(NULL);
      // initialize the random number generator
      MTRand rng(rngSeed);

      // initialize the BRKGA-based heuristic
      int i = 1, curtime = 0;
      time_t TStop = time(NULL);
      curtime = TStop - TStart;

      // cout << "Initializing decoder at " << curtime << " seconds"<< endl;
      BRKGA< BRKGADecoder, MTRand >
      algorithm(n, p, pe, pm, rhoe, decoder, rng, K, MAXT);

      TStop = time(NULL);
      curtime = TStop - TStart;
      // cout << "Conclusion of decoder at " << curtime << " seconds"<< endl;

      // current generation
      unsigned generation = 0;
      // exchange best individuals at every 100 generations
      const unsigned X_INTVL = 100;
      // exchange top 2 best
      const unsigned X_NUMBER = 2;
      // run for 1000 gens
      const unsigned MAX_GENS = 1000;

      do {
        TStop = time(NULL);
        curtime = TStop - TStart;
        // cout << "Starting Generation " << i <<
        // " at " << curtime << " seconds" <<endl;
        // evolve the population for one generation
        algorithm.evolve();
        if ( (++generation) % X_INTVL == 0 ) {
          // exchange top individuals
          algorithm.exchangeElite(X_NUMBER);
        }

        time_t TStop = time(NULL);
        curtime = TStop - TStart;
        // cout << "Stoping Generation " << i <<
        // " at " << curtime << " seconds" <<endl;
        i++;
      } while ((generation < MAX_GENS) && (curtime < time_for_execution));
      // cout << "TOTAL EXECUTION TIME: " << curtime << endl;

      fout << (algorithm.getBestFitness() / order) << ";\n";
      cout << "BRKGA execution " << j << " for " << "'" << net_name << "' finished" << endl;
      Sleep(delay_time);
    }
    fout << endl;
    cout << "Finishing BRKGA for '" << net_name << "'\n\n";

    //IGS
    fout << "IGS SECTION" << endl;
    for(int j = 0; j < qt_executions; j++) {
      cout << "Starting IGS execution " << j << " for '" << net_name << "'\n";

      Graph g_igs(net_name, 0);
      Demand d_igs(dem_name, 0);
      //Greedy greedy(g_igs, d_igs);
      IGS igs;
      fout << (igs.execute(g_igs, d_igs, time_for_execution) / order) << ";\n";
      // cout << (igs.execute(greedy, time_for_execution) / order) << endl;
      cout << "IGS execution " << j << " for " << "'" << net_name << "' finished" << endl;
      Sleep(delay_time);
    }
    fout << endl;
    cout << "Finishing IGS for '" << net_name << "'\n\n";
    fout.close();

  }
  system("PAUSE");
  return 0;
}
