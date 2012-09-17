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
#include "./psc.h"
#include "./mspsc.h"
#include "./vns.h"
#include "./differentialevolution.h"

using std::cin;
using std::stringstream;
using std::string;

std::string tostring(double x)
{
  std::ostringstream oss;
  oss << x;
  return oss.str();
}


int main(int argc, char *argv[]) {
  srand(time(NULL));

  std::vector<double> igs_k_;
//  igs_k_.push_back(0.05);
  igs_k_.push_back(0.1);
//  igs_k_.push_back(0.15);
  igs_k_.push_back(0.2);
//  igs_k_.push_back(0.25);
  igs_k_.push_back(0.3);
  /*  igs_k_.push_back(0.35);
    igs_k_.push_back(0.4);
    igs_k_.push_back(0.45);
    igs_k_.push_back(0.5);
    igs_k_.push_back(0.55);
    igs_k_.push_back(0.6);
    igs_k_.push_back(0.65);
    igs_k_.push_back(0.7);
    igs_k_.push_back(0.75);
    igs_k_.push_back(0.8);
    igs_k_.push_back(0.85);
    igs_k_.push_back(0.9);
    igs_k_.push_back(0.95);
    igs_k_.push_back(1); */

  std::vector<double> igs_beta_;
  igs_beta_.push_back(0);
  igs_beta_.push_back(0.05);
  igs_beta_.push_back(0.1);
  /*  igs_beta_.push_back(0.2);

    /*  igs_beta_.push_back(0.1);
      igs_beta_.push_back(0.2);
      igs_beta_.push_back(0.3);
      igs_beta_.push_back(0.4);
      igs_beta_.push_back(0.5);
      igs_beta_.push_back(0.6);
      igs_beta_.push_back(0.7);
      igs_beta_.push_back(0.8);
      igs_beta_.push_back(0.9);*/

  std::vector<int> igs_x_;
  /*  igs_x_.push_back(0);
    igs_x_.push_back(10);
    igs_x_.push_back(20);
    igs_x_.push_back(30);
    igs_x_.push_back(40);
    igs_x_.push_back(50);
    igs_x_.push_back(60);
    igs_x_.push_back(70);
    igs_x_.push_back(80);
    igs_x_.push_back(90);*/
  igs_x_.push_back(25);
  igs_x_.push_back(50);
  igs_x_.push_back(100);


  cout.precision(50);
  int qt_executions = 5, delay_time = 30, time_for_execution_original = 600,
                                      order = 1;
  time_t TStart, TStop;
  //string instance_folder = "F:/Instance/";
  string instance_folder = "c:/PIFRO/instances/";
  string instance_out = "c:/PIFRO/results/";

  std::vector<string> instances;
//  instances.push_back("abilene"); // n
  /*  instances.push_back("atlanta"); // n
    instances.push_back("cost266");
    instances.push_back("dfn-bwin"); // n
    instances.push_back("dfn-gwin"); // n
    instances.push_back("di-yuan"); // n
    instances.push_back("france");
    instances.push_back("geant"); // n */
  /*  instances.push_back("germany50");
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
    instances.push_back("ta2"); */
  instances.push_back("zib54");

  std::vector<int> de_a;
  de_a.push_back(0);
  de_a.push_back(1);
//  de_a.push_back(2); --> Executar depois

  std::vector<int> de_b;
  de_b.push_back(1);
  //de_b.push_back(2);

  std::vector<int> de_c;
  de_c.push_back(0);
  // de_c.push_back(1);

  std::vector<int> vns_it;
  vns_it.push_back(5);
  vns_it.push_back(10);
  vns_it.push_back(20);

  bool greedy_exec_ = false, psc_exec_ = false, mspsc_exec_ = false,
  brkga_greedy_exec_= false, brkga_psc_exec_ = false, msbrkga_greedy_exec_= false, msbrkga_psc_exec_ = false,
  igs_greedy_minor_exec_ = true, igs_greedy_minor_equal_exec_ = false, igs_greedy_minor_x_exec_ = false, igs_greedy_minor_equal_x_exec_ = false,
  igs_psc_minor_exec_ = false, igs_psc_minor_equal_exec_ = false, igs_psc_minor_x_exec_ = false, igs_psc_minor_equal_x_exec_ = false,
  vns_greedy_minor_exec_ = true, vns_greedy_minor_equal_exec_ = false, vns_psc_minor_exec_ = false, vns_psc_minor_equal_exec_ = false,
  de_greedy_exec_ = false, de_psc_exec_ = false;



  // GREEDY
  if(greedy_exec_) {
    for (int f = 0; f < instances.size(); f++) {
      string output(instance_out + "/GREEDY/GREEDY_" + instances[f] + ".txt");
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

      // fout << "GREEDY;BRKGA;IGS;" << endl;
      fout << "GREEDY;" << endl;
      for (int j = 0; j < qt_executions; j++) {
        cout << "Starting GREEDY execution " <<
             j << " for '" << net_name << "'\n";
        // TStart = time(NULL);
        g.CleanCosts();
        d.Sort();
        Greedy greedy(g, d);
        // greedy.Execute(true, false);
        TStart = time(NULL);
        fout << (greedy.ExecuteWithRefine(true, false, TStart, time_for_execution_original) / order) << ";\n";
        cout << "Greedy execution " << j
             << " for " << "'" << net_name << "' finished at " << (time(NULL) - TStart) << " seconds " << endl;
        Sleep(delay_time);
        cout << "Finishing Greedy for '" << net_name << "'\n\n";
      }
      fout.close();
    }
  }


  // PSC
  if(psc_exec_) {
    for (int f = 0; f < instances.size(); f++) {
      string output(instance_out + "/PSC/PSC_" + instances[f] + ".txt");
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

      fout << "PSC;" << endl;
      for (int j = 0; j < qt_executions; j++) {
        cout << "Starting PSC execution " <<
             j << " for '" << net_name << "'\n";
        g.CleanCosts();
        d.Sort();
        PSC psc(g, d);

        TStart = time(NULL);
        fout << (psc.ExecuteWithRefine(true, false, TStart, time_for_execution_original) / order) << ";\n";
        cout << "PSC execution " << j
             << " for " << "'" << net_name << "' finished at " << (time(NULL) - TStart) << " seconds " << endl;
        Sleep(delay_time);
        cout << "Finishing PSC for '" << net_name << "'\n\n";
      }
      fout.close();
    }
  }

  // MSPSC
  if(mspsc_exec_) {
    for (int f = 0; f < instances.size(); f++) {
      string output(instance_out + "/MSPSC/MSPSC_" + instances[f] + ".txt");
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

      fout << "MSPSC;" << endl;
      for (int j = 0; j < qt_executions; j++) {
        // time_for_execution = curtime;
        cout << "Starting MSPSC execution " << j << " for '" << net_name << "'\n";

        TStart = time(NULL);
        g.CleanCosts();
        d.Sort();
        MSPSC mspsc;
        fout << (mspsc.execute(g, d, time_for_execution_original) / order) << ";\n";
        cout << "MSPSC execution " << j
             << " for " << "'" << net_name << "' finished at " << (time(NULL) - TStart) << " seconds" << endl;
        cout << "Finishing MSPSC for '" << net_name << "'\n\n";
        Sleep(delay_time);

      }
      fout.close();
    }
  }

  // BRKGA_GREEDY
  if(brkga_greedy_exec_) {
    for (int f = 0; f < instances.size(); f++) {
      string output(instance_out + "/BRKGA/GREEDY/BRKGA_G_" + instances[f] + ".txt");
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

      fout << "BRKGA;" << endl;
      for (int j = 0; j < qt_executions; j++) {
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
        BRKGADecoder decoder(g, d, TStart, time_for_execution_original, 0);

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

        fout << (algorithm.getBestFitness() / order) << ";\n";
        cout << "BRKGA execution " << j
             << " for " << "'" << net_name << "' finished at " << curtime << " seconds" << endl;
        Sleep(delay_time);
        cout << "Finishing BRKGA for '" << net_name << "'\n\n";
      }
      fout.close();
    }
  }


  // BRKGA_PSC
  if(brkga_psc_exec_) {
    for (int f = 0; f < instances.size(); f++) {
      string output(instance_out + "/BRKGA/PSC/BRKGA_P_" + instances[f] + ".txt");
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

      fout << "BRKGA;" << endl;
      for (int j = 0; j < qt_executions; j++) {
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
        BRKGADecoder decoder(g, d, TStart, time_for_execution_original, 1);

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

        fout << (algorithm.getBestFitness() / order) << ";\n";
        cout << "BRKGA execution " << j
             << " for " << "'" << net_name << "' finished at " << curtime << " seconds" << endl;
        Sleep(delay_time);
        cout << "Finishing BRKGA for '" << net_name << "'\n\n";
      }
      fout.close();
    }
  }


  // MSBRKGA_GREEDY
  if(msbrkga_greedy_exec_) {
    for (int f = 0; f < instances.size(); f++) {
      string output(instance_out + "/BRKGA/GREEDY/MSBRKGA_G_" + instances[f] + ".txt");
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

      fout << "MSBRKGA;" << endl;
      for (int j = 0; j < qt_executions; j++) {
        int  curtime = 0;
        cout << "Starting MSBRKGA execution " << j << " for '" << net_name << "'\n";
        TStart = time(NULL);

        g.CleanCosts();
        d.Sort();

        // size of chromosomes
        const unsigned n = d.qt_request_;
        // size of population
        const unsigned p = g.qt_vertex_;
        // fraction of population to be the elite-set
        const double pe = 0.01;
        // fraction of population to be replaced by mutants
        const double pm = 0.0;
        // probability that offspring inherit an allele from elite parent
        const double rhoe = 0.99;
        // number of independent populations
        const unsigned K = 1;
        // number of threads for parallel decoding
        const unsigned MAXT = 1;

        // initialize the decoder
        BRKGADecoder decoder(g, d, TStart, time_for_execution_original, 0);

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

        fout << (algorithm.getBestFitness() / order) << ";\n";
        cout << "MSBRKGA execution " << j
             << " for " << "'" << net_name << "' finished at " << curtime << " seconds" << endl;
        Sleep(delay_time);
        cout << "Finishing MSBRKGA for '" << net_name << "'\n\n";
      }
      fout.close();
    }
  }

  // MSBRKGA_PSC
  if(msbrkga_psc_exec_) {
    for (int f = 0; f < instances.size(); f++) {
      string output(instance_out + "/BRKGA/PSC/MSBRKGA_P_" + instances[f] + ".txt");
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

      fout << "MSBRKGA;" << endl;
      for (int j = 0; j < qt_executions; j++) {
        int  curtime = 0;
        cout << "Starting MSBRKGA execution " << j << " for '" << net_name << "'\n";
        TStart = time(NULL);

        g.CleanCosts();
        d.Sort();

        // size of chromosomes
        const unsigned n = d.qt_request_;
        // size of population
        const unsigned p = g.qt_vertex_;
        // fraction of population to be the elite-set
        const double pe = 0.01;
        // fraction of population to be replaced by mutants
        const double pm = 0.0;
        // probability that offspring inherit an allele from elite parent
        const double rhoe = 0.99;
        // number of independent populations
        const unsigned K = 1;
        // number of threads for parallel decoding
        const unsigned MAXT = 1;

        // initialize the decoder
        BRKGADecoder decoder(g, d, TStart, time_for_execution_original, 1);

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

        fout << (algorithm.getBestFitness() / order) << ";\n";
        cout << "MSBRKGA execution " << j
             << " for " << "'" << net_name << "' finished at " << curtime << " seconds" << endl;
        Sleep(delay_time);
        cout << "Finishing MSBRKGA for '" << net_name << "'\n\n";
      }
      fout.close();
    }
  }


  // IGS_GREEDY_MINOR
  if(igs_greedy_minor_exec_) {
    for (int f = 0; f < instances.size(); f++) {
      for(int a = 0; a < igs_k_.size(); a++) {
        for(int b = 0; b < igs_beta_.size(); b++) {
          string output(instance_out + "/IGS/GREEDY/IGS_GM_" + instances[f] + "_k_" + tostring(igs_k_[a]) + "_b_" + tostring(igs_beta_[b]) + ".txt");
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

          fout << "IGS;" << endl;
          for (int j = 0; j < qt_executions; j++) {
            // time_for_execution = curtime;
            cout << "Starting IGS execution " << j << " for '" << net_name << "'\n";

            TStart = time(NULL);
            g.CleanCosts();
            d.Sort();
            IGS igs;
            fout << (igs.executeWithGreedyMinor(g, d, time_for_execution_original, igs_k_[a], igs_beta_[b], true) / order) << ";\n";
            cout << "IGS execution " << j
                 << " for " << "'" << net_name << "' finished at " << (time(NULL) - TStart) << " seconds" << endl;
            cout << "Finishing IGS for '" << net_name << "'\n\n";
            Sleep(delay_time);

          }
          fout.close();
        }
      }
    }
  }

  // IGS_GREEDY_MINOR_EQUAL
  if(igs_greedy_minor_equal_exec_) {
    for (int f = 0; f < instances.size(); f++) {
      for(int a = 0; a < igs_k_.size(); a++) {
//        for(int b = 0; b < igs_beta_.size(); b++){
        string output(instance_out + "/IGS/GREEDY/IGS_GME_" + instances[f] + "_k_" + tostring(igs_k_[a]) + ".txt");
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

        fout << "IGS;" << endl;
        for (int j = 0; j < qt_executions; j++) {
          // time_for_execution = curtime;
          cout << "Starting IGS execution " << j << " for '" << net_name << "'\n";

          TStart = time(NULL);
          g.CleanCosts();
          d.Sort();
          IGS igs;
          fout << (igs.executeWithGreedyMinorEqual(g, d, time_for_execution_original, igs_k_[a], 0, true) / order) << ";\n";
          cout << "IGS execution " << j
               << " for " << "'" << net_name << "' finished at " << (time(NULL) - TStart) << " seconds" << endl;
          cout << "Finishing IGS for '" << net_name << "'\n\n";
          Sleep(delay_time);

        }
        fout.close();
//        }
      }
    }
  }

  // IGS_GREEDY_MINOR_X
  if(igs_greedy_minor_x_exec_) {
    for (int f = 0; f < instances.size(); f++) {
      for(int a = 0; a < igs_k_.size(); a++) {
        for(int b = 0; b < igs_beta_.size(); b++) {
          for(int c = 0; c < igs_x_.size(); c++) {
            string output(instance_out + "/IGS/GREEDY/IGS_GMX_" + instances[f] + "_k_" + tostring(igs_k_[a]) + "_b_" + tostring(igs_beta_[b]) +
                          "_x_" + tostring(igs_x_[c]) + ".txt");
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

            fout << "IGS;" << endl;
            for (int j = 0; j < qt_executions; j++) {
              // time_for_execution = curtime;
              cout << "Starting IGS execution " << j << " for '" << net_name << "'\n";

              TStart = time(NULL);
              g.CleanCosts();
              d.Sort();
              IGS igs;
              fout << (igs.executeWithGreedyMinorX(g, d, time_for_execution_original, igs_k_[a], igs_beta_[b], igs_x_[c], true) / order) << ";\n";
              cout << "IGS execution " << j
                   << " for " << "'" << net_name << "' finished at " << (time(NULL) - TStart) << " seconds" << endl;
              cout << "Finishing IGS for '" << net_name << "'\n\n";
              Sleep(delay_time);

            }
            fout.close();
          }
        }
      }
    }
  }


  // IGS_GREEDY_MINOR_EQUAL_X
  if(igs_greedy_minor_equal_x_exec_) {
    for (int f = 0; f < instances.size(); f++) {
      for(int a = 0; a < igs_k_.size(); a++) {
//        for(int b = 0; b < igs_beta_.size(); b++){
        for(int c = 0; c < igs_x_.size(); c++) {
          string output(instance_out + "/IGS/GREEDY/IGS_GMEX_" + instances[f] + "_k_" + tostring(igs_k_[a]) + "_x_" + tostring(igs_x_[c]) + ".txt");
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

          fout << "IGS;" << endl;
          for (int j = 0; j < qt_executions; j++) {
            // time_for_execution = curtime;
            cout << "Starting IGS execution " << j << " for '" << net_name << "'\n";

            TStart = time(NULL);
            g.CleanCosts();
            d.Sort();
            IGS igs;
            fout << (igs.executeWithGreedyMinorEqualX(g, d, time_for_execution_original, igs_k_[a], 0, igs_x_[c], true) / order) << ";\n";
            cout << "IGS execution " << j
                 << " for " << "'" << net_name << "' finished at " << (time(NULL) - TStart) << " seconds" << endl;
            cout << "Finishing IGS for '" << net_name << "'\n\n";
            Sleep(delay_time);

          }
          fout.close();
        }
//        }
      }
    }
  }

  // IGS_PSC_MINOR
  if(igs_psc_minor_exec_) {
    for (int f = 0; f < instances.size(); f++) {
      for(int a = 0; a < igs_k_.size(); a++) {
        for(int b = 0; b < igs_beta_.size(); b++) {
          string output(instance_out + "/IGS/PSC/IGS_PM_" + instances[f] + "_k_" + tostring(igs_k_[a]) + "_b_" + tostring(igs_beta_[b]) + ".txt");
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

          fout << "IGS;" << endl;
          for (int j = 0; j < qt_executions; j++) {
            // time_for_execution = curtime;
            cout << "Starting IGS execution " << j << " for '" << net_name << "'\n";

            TStart = time(NULL);
            g.CleanCosts();
            d.Sort();
            IGS igs;
            fout << (igs.executeWithPSCMinor(g, d, time_for_execution_original, igs_k_[a], igs_beta_[b], true) / order) << ";\n";
            cout << "IGS execution " << j
                 << " for " << "'" << net_name << "' finished at " << (time(NULL) - TStart) << " seconds" << endl;
            cout << "Finishing IGS for '" << net_name << "'\n\n";
            Sleep(delay_time);

          }
          fout.close();
        }
      }
    }
  }

  // IGS_PSC_MINOR_EQUAL
  if(igs_psc_minor_equal_exec_) {
    for (int f = 0; f < instances.size(); f++) {
      for(int a = 0; a < igs_k_.size(); a++) {
//        for(int b = 0; b < igs_beta_.size(); b++){
        string output(instance_out + "/IGS/PSC/IGS_PME_" + instances[f] + "_k_" + tostring(igs_k_[a]) + ".txt");
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

        fout << "IGS;" << endl;
        for (int j = 0; j < qt_executions; j++) {
          // time_for_execution = curtime;
          cout << "Starting IGS execution " << j << " for '" << net_name << "'\n";

          TStart = time(NULL);
          g.CleanCosts();
          d.Sort();
          IGS igs;
          fout << (igs.executeWithPSCMinorEqual(g, d, time_for_execution_original, igs_k_[a], 0, true) / order) << ";\n";
          cout << "IGS execution " << j
               << " for " << "'" << net_name << "' finished at " << (time(NULL) - TStart) << " seconds" << endl;
          cout << "Finishing IGS for '" << net_name << "'\n\n";
          Sleep(delay_time);

        }
        fout.close();
//        }
      }
    }
  }


  // IGS_PSC_MINOR_X_
  if(igs_psc_minor_x_exec_) {
    for (int f = 0; f < instances.size(); f++) {
      for(int a = 0; a < igs_k_.size(); a++) {
        for(int b = 0; b < igs_beta_.size(); b++) {
          for(int c = 0; c < igs_x_.size(); c++) {
            string output(instance_out + "/IGS/PSC/IGS_PMX_" + instances[f] + "_k_" + tostring(igs_k_[a]) + "_b_" + tostring(igs_beta_[b]) +
                          "_x_" + tostring(igs_x_[c]) + ".txt");
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

            fout << "IGS;" << endl;
            for (int j = 0; j < qt_executions; j++) {
              // time_for_execution = curtime;
              cout << "Starting IGS execution " << j << " for '" << net_name << "'\n";

              TStart = time(NULL);
              g.CleanCosts();
              d.Sort();
              IGS igs;
              fout << (igs.executeWithPSCMinorX(g, d, time_for_execution_original, igs_k_[a], igs_beta_[b], igs_x_[c], true) / order) << ";\n";
              cout << "IGS execution " << j
                   << " for " << "'" << net_name << "' finished at " << (time(NULL) - TStart) << " seconds" << endl;
              cout << "Finishing IGS for '" << net_name << "'\n\n";
              Sleep(delay_time);

            }
            fout.close();
          }
        }
      }
    }
  }

  // IGS_PSC_MINOR_EQUAL_X
  if(igs_psc_minor_equal_x_exec_) {
    for (int f = 0; f < instances.size(); f++) {
      for(int a = 0; a < igs_k_.size(); a++) {
//        for(int b = 0; b < igs_beta_.size(); b++){
        for(int c = 0; c < igs_x_.size(); c++) {
          string output(instance_out + "/IGS/PSC/IGS_PMEX_" + instances[f] + "_k_" + tostring(igs_k_[a]) + "_x_" + tostring(igs_x_[c]) + ".txt");
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

          fout << "IGS;" << endl;
          for (int j = 0; j < qt_executions; j++) {
            // time_for_execution = curtime;
            cout << "Starting IGS execution " << j << " for '" << net_name << "'\n";

            TStart = time(NULL);
            g.CleanCosts();
            d.Sort();
            IGS igs;
            fout << (igs.executeWithPSCMinorEqualX(g, d, time_for_execution_original, igs_k_[a], 0, igs_x_[c], true) / order) << ";\n";
            cout << "IGS execution " << j
                 << " for " << "'" << net_name << "' finished at " << (time(NULL) - TStart) << " seconds" << endl;
            cout << "Finishing IGS for '" << net_name << "'\n\n";
            Sleep(delay_time);

          }
          fout.close();
        }
//        }
      }
    }
  }



  // VNS_GREEDY_MINOR
  if(vns_greedy_minor_exec_) {
    for(int b = 0; b < igs_beta_.size(); b++) {
      for(int a = 0; a < vns_it.size(); a++) {
        for (int f = 0; f < instances.size(); f++) {
//      for(int a = 0; a < igs_k_.size(); a++){
          string output(instance_out + "/VNS/GREEDY/VNS_GM_" + instances[f] + "_b_" + tostring(igs_beta_[b]) + "_it_" + tostring(vns_it[a]) + ".txt");
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

          fout << "VNS;" << endl;
          for (int j = 0; j < qt_executions; j++) {
            // time_for_execution = curtime;
            cout << "Starting VNS execution " << j << " for '" << net_name << "'\n";

            TStart = time(NULL);
            g.CleanCosts();
            d.Sort();
            VNS vns;
            fout << (vns.executeWithGreedyMinor(g, d, time_for_execution_original, igs_beta_[b], 0.1, 0.3, 0.01, vns_it[a]) / order) << ";\n";
            cout << "VNS execution " << j
                 << " for " << "'" << net_name << "' finished at " << (time(NULL) - TStart) << " seconds" << endl;
            cout << "Finishing VNS for '" << net_name << "'\n\n";
            Sleep(delay_time);

          }
          fout.close();
//        }
        }
      }
    }
  }

  // VNS_GREEDY_MINOR_EQUAL
  if(vns_greedy_minor_equal_exec_) {
    for (int f = 0; f < instances.size(); f++) {
      for(int a = 0; a < vns_it.size(); a++) {
//      for(int a = 0; a < igs_k_.size(); a++){
//        for(int b = 0; b < igs_beta_.size(); b++){
        string output(instance_out + "/VNS/GREEDY/VNS_GME_" + instances[f] + "_it_" + tostring(vns_it[a]) + ".txt");
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

        fout << "VNS;" << endl;
        for (int j = 0; j < qt_executions; j++) {
          // time_for_execution = curtime;
          cout << "Starting VNS execution " << j << " for '" << net_name << "'\n";

          TStart = time(NULL);
          g.CleanCosts();
          d.Sort();
          VNS vns;
          fout << (vns.executeWithGreedyMinorEqual(g, d, time_for_execution_original, 0.1, 0.3, 0.01, vns_it[a]) / order) << ";\n";
          cout << "VNS execution " << j
               << " for " << "'" << net_name << "' finished at " << (time(NULL) - TStart) << " seconds" << endl;
          cout << "Finishing VNS for '" << net_name << "'\n\n";
          Sleep(delay_time);

        }
        fout.close();
//        }
      }
    }
  }


  // VNS_PSC_MINOR
  if(vns_psc_minor_exec_) {
    for(int b = 0; b < igs_beta_.size(); b++) {
      for(int a = 0; a < vns_it.size(); a++) {
        for (int f = 0; f < instances.size(); f++) {
//      for(int a = 0; a < igs_k_.size(); a++){
          string output(instance_out + "/VNS/PSC/VNS_PM_" + instances[f] + "_b_" + tostring(igs_beta_[b])  + "_it_" + tostring(vns_it[a]) + ".txt");
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

          fout << "VNS;" << endl;
          for (int j = 0; j < qt_executions; j++) {
            // time_for_execution = curtime;
            cout << "Starting VNS execution " << j << " for '" << net_name << "'\n";

            TStart = time(NULL);
            g.CleanCosts();
            d.Sort();
            VNS vns;
            fout << (vns.executeWithPSCMinor(g, d, time_for_execution_original, igs_beta_[b], 0.1, 0.3, 0.01, vns_it[a]) / order) << ";\n";
            cout << "VNS execution " << j
                 << " for " << "'" << net_name << "' finished at " << (time(NULL) - TStart) << " seconds" << endl;
            cout << "Finishing VNS for '" << net_name << "'\n\n";
            Sleep(delay_time);

          }
          fout.close();
//        }
        }
      }
    }
  }

  // VNS_PSC_MINOR_EQUAL
  if(vns_psc_minor_equal_exec_) {
    for (int f = 0; f < instances.size(); f++) {
      for(int a = 0; a < vns_it.size(); a++) {
//      for(int a = 0; a < igs_k_.size(); a++){
//        for(int b = 0; b < igs_beta_.size(); b++){
        string output(instance_out + "/VNS/PSC/VNS_PME_" + instances[f]  + "_it_" + tostring(vns_it[a]) + ".txt");
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

        fout << "VNS;" << endl;
        for (int j = 0; j < qt_executions; j++) {
          // time_for_execution = curtime;
          cout << "Starting VNS execution " << j << " for '" << net_name << "'\n";

          TStart = time(NULL);
          g.CleanCosts();
          d.Sort();
          VNS vns;
          fout << (vns.executeWithPSCMinorEqual(g, d, time_for_execution_original, 0.1, 0.3, 0.01, vns_it[a]) / order) << ";\n";
          cout << "VNS execution " << j
               << " for " << "'" << net_name << "' finished at " << (time(NULL) - TStart) << " seconds" << endl;
          cout << "Finishing VNS for '" << net_name << "'\n\n";
          Sleep(delay_time);

        }
        fout.close();
//        }
      }
    }
  }



  //DIFFERENTIAL EVOLUTION GREEDY
  if(de_greedy_exec_) {
    for (int f = 0; f < instances.size(); f++) {
      for(int a = 0; a < de_a.size(); a++) {
        for(int b = 0; b < de_b.size(); b++) {
          for(int c = 0; c < de_c.size(); c++) {
            string output(instance_out + "/DE/GREEDY/DE_" + instances[f] + "_a_" + tostring(de_a[a]) + "_b_" + tostring(de_b[b]) +
                          "_c_" + tostring(de_c[c]) + ".txt");
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

            fout << "DE;" << endl;
            for (int j = 0; j < qt_executions; j++) {
              // time_for_execution = curtime;
              cout << "Starting DE GREEDY execution " << j << " for '" << net_name << "'\n";

              TStart = time(NULL);
              g.CleanCosts();
              d.Sort();
              DifferentialEvolution de(g, d, TStart, time_for_execution_original, 0, d.vec_request_.size(), 70 , 0.2, 0.8, de_a[a], de_b[b], de_c[c]);
              fout << (de.evolve() / order) << ";\n";
              cout << "DE GREEDY execution " << j
                   << " for " << "'" << net_name << "' finished at " << (time(NULL) - TStart) << " seconds" << endl;
              cout << "Finishing DE for '" << net_name << " - Cost: " << de.min_cost_ << "'\n\n";
              Sleep(delay_time);
              system("PAUSE");

            }
            fout.close();
          }
        }
      }
    }
  }


  //DIFFERENTIAL EVOLUTION PSC
  if(de_psc_exec_) {
    for (int f = 0; f < instances.size(); f++) {
      for(int a = 0; a < de_a.size(); a++) {
        for(int b = 0; b < de_b.size(); b++) {
          for(int c = 0; c < de_c.size(); c++) {
            string output(instance_out + "/DE/PSC/DE_" + instances[f] + "_a_" + tostring(de_a[a]) + "_b_" + tostring(de_b[b]) +
                          "_c_" + tostring(de_c[c]) + ".txt");
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

            fout << "DE;" << endl;
            for (int j = 0; j < qt_executions; j++) {
              // time_for_execution = curtime;
              cout << "Starting DE PSC execution " << j << " for '" << net_name << "'\n";

              TStart = time(NULL);
              g.CleanCosts();
              d.Sort();
              DifferentialEvolution de(g, d, TStart, time_for_execution_original, 1, d.vec_request_.size(), g.qt_vertex_, 0.7, 0.8, de_a[a], de_b[b], de_c[c]);
              fout << (de.evolve() / order) << ";\n";
              cout << "DE PSC execution " << j
                   << " for " << "'" << net_name << "' finished at " << (time(NULL) - TStart) << " seconds" << endl;
              cout << "Finishing DE for '" << net_name << " - Cost: " << de.min_cost_ << "'\n\n";
              Sleep(delay_time);

            }
            fout.close();
          }
        }
      }
    }
  }

  system("PAUSE");
  return 0;
}
