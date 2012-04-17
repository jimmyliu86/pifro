// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#include <time.h>
#include <cstdlib>
#include <vector>

#include "./Vertex.h"
#include "./Graph.h"
#include "./Demand.h"
#include "./Dijkstra.h"
#include "./Greedy.h"
#include "./rvgs.h"
#include "./MTRand.h"
#include "./BRKGA.h"
#include "./BRKGADecoder.h"

int main(int argc, char *argv[]) {
  cout.precision(50);

  // Greedy
  Graph g("f:/instance1/abilene/abilene.net", 0);
  g.printWithWeight();
  g.printWithCost();
  g.printWithQtRequests();

  cout << endl << endl;

  Demand d("f:/instance1/abilene/abilene.trf",
           0, g.getAdjList(), g.getQtVertex());

  Greedy greedy;
  cout << "\n\n\nGREEDY COST: US$ " <<
       (greedy.executeWithRefine(g, d.getVecRequest())) / 1000000 << endl;
  g.printWithQtRequests();

  // BRKGA
  Graph g2("f:/instance1/abilene/abilene.net", 0);
  Demand d2("f:/instance1/abilene/abilene.trf",
            0, g2.getAdjList(), g2.getQtVertex());
  int seconds = 1200;

  time_t TStart = time(NULL);

  // size of chromosomes
  const unsigned n = d2.getVecRequest().size();
  // size of population
  // const unsigned p = 1000;
  const unsigned p = 100;
  // fraction of population to be the elite-set
  const double pe = 0.30;
  // fraction of population to be replaced by mutants
  const double pm = 0.15;
  // probability that offspring inherit an allele from elite parent
  const double rhoe = 0.70;
  // number of independent populations
  const unsigned K = 3;
  // number of threads for parallel decoding
  const unsigned MAXT = 2;

  // initialize the decoder
  BRKGADecoder decoder(g2, d2.getVecRequest());

  // seed to the random number generator
  const float rngSeed = 0;
  // initialize the random number generator
  MTRand rng(rngSeed);

  // initialize the BRKGA-based heuristic
  int i = 1, curtime = 0;
  time_t TStop = time(NULL);
  curtime = TStop - TStart;

  cout << "Initializing decoder at " << curtime << " seconds"<< endl;
  BRKGA< BRKGADecoder, MTRand >
            algorithm(n, p, pe, pm, rhoe, decoder, rng, K, MAXT);

  TStop = time(NULL);
  curtime = TStop - TStart;
  cout << "Conclusion of decoder at " << curtime << " seconds"<< endl;

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
    cout << "Starting Generation " << i <<
         " at " << curtime << " seconds" <<endl;
    // evolve the population for one generation
    algorithm.evolve();
    if ( (++generation) % X_INTVL == 0 ) {
      // exchange top individuals
      algorithm.exchangeElite(X_NUMBER);
    }

    time_t TStop = time(NULL);
    curtime = TStop - TStart;
    cout << "Stoping Generation " << i <<
            " at " << curtime << " seconds" <<endl;
    i++;
  } while ((generation < MAX_GENS) && (curtime < seconds));
  cout << "TOTAL EXECUTION TIME: " << curtime << endl;

  cout << "Best Fitness for BRKGAWithGreedy: US$ "
       << algorithm.getBestFitness() / 1000000 << endl;

  return 0;
}
