#include <cstdlib>
#include <iostream>


#include <time.h>
#include "Vertex.h"
#include "Graph.h"
#include "Demand.h"
#include "Dijkstra.h"
#include "Greedy.h"
#include "rvgs.h"

#include "MTRand.h"
#include "BRKGA.h"
#include "BRKGADecoder.h"

using namespace std;

float executeBRKGAGreedy(Graph& graph, std::vector<Request>& vecrequest, int seconds)
{
    time_t TStart = time(NULL);

    const unsigned n = vecrequest.size();		// size of chromosomes
	const unsigned p = 100;	// size of population
	const double pe = 0.30;		// fraction of population to be the elite-set
	const double pm = 0.15;		// fraction of population to be replaced by mutants
	const double rhoe = 0.70;	// probability that offspring inherit an allele from elite parent
	const unsigned K = 3;		// number of independent populations
	const unsigned MAXT = 2;	// number of threads for parallel decoding

	BRKGADecoder decoder(graph, vecrequest);			// initialize the decoder

	const long unsigned rngSeed = 0;	// seed to the random number generator
	MTRand rng(rngSeed);				// initialize the random number generator

	// initialize the BRKGA-based heuristic

    int i = 1, curtime = 0;
    time_t TStop = time(NULL);
    curtime = TStop - TStart;

    cout << "Initializing decoder at " << curtime << " seconds"<< endl;
	BRKGA< BRKGADecoder, MTRand > algorithm(n, p, pe, pm, rhoe, decoder, rng, K, MAXT);

	TStop = time(NULL);
    curtime = TStop - TStart;
    cout << "Conclusion of decoder at " << curtime << " seconds"<< endl;

	unsigned generation = 0;		// current generation
	const unsigned X_INTVL = 100;	// exchange best individuals at every 100 generations
	const unsigned X_NUMBER = 2;	// exchange top 2 best
	const unsigned MAX_GENS = 1000;	// run for 1000 gens

	do {
        TStop = time(NULL);
	    curtime = TStop - TStart;
	    cout << "Starting Generation " << i << " at " << curtime << " seconds" <<endl;
	    algorithm.evolve();	// evolve the population for one generation
		if((++generation) % X_INTVL == 0) {
			algorithm.exchangeElite(X_NUMBER);	// exchange top individuals
		}

		time_t TStop = time(NULL);
		curtime = TStop - TStart;
	    cout << "Stoping Generation " << i << " at " << curtime << " seconds" <<endl;
	    i++;
	} while ((generation < MAX_GENS) && (curtime < seconds));
    cout << "TOTAL EXECUTION TIME: " << curtime << endl;
	/*std::cout << "Best solution found has objective value = "
	 		<< algorithm.getBestFitness() << std::endl;*/

	return algorithm.getBestFitness();
}

int main(int argc, char *argv[])
{

    //Vertex v(1,0,123223.9880);
    //v.print();
    //Vertex tmp(2,0,0);
    //Vertex tmp2(1,0,0);

    cout.precision(100);

    Graph g("f:/instance1/abilene/abilene.net",0);
    //g.loadFromSNDFile("abilene.net");
    //g.addEdge(2,1);
    g.printWithWeight();
    g.printWithCost();
    g.printWithQtRequests();

    cout << endl << endl;

    Demand d("f:/instance1/abilene/abilene.trf",0, g.getAdjList(), g.getQtVertex());
    //d.print();

    //Dijkstra dij;
    //float x = dij.getCostByDijkstra(g.getAdjList(), g.getQtVertex(), 1, 2);
    //cout << "Custo Dijkstra: " << x << endl;

    Greedy greedy;
    //cout.precision(50);
    cout << "\n\n\nGREEDY COST: US$ " << (greedy.executeWithRefine(g, d.getVecRequest())) / 1000000 << endl;
    g.printWithQtRequests();
    //system("PAUSE");


    Graph g2("f:/instance1/abilene/abilene.net",0);
    Demand d2("f:/instance1/abilene/abilene.trf",0, g.getAdjList(), g.getQtVertex());
    //BRKGA ga(100, 20, 70, 10, 0.70f, d2.getVecRequest(), g2);
    //cout << "Best Fitness for BRKGAWithGreedy: US$ " << ga.ExecuteWithGreedy(600) / 1000000 << endl;
    cout << "Best Fitness for BRKGAWithGreedy: US$ " << executeBRKGAGreedy(g2, d2.getVecRequest(),300) / 1000000 << endl;
    //system("PAUSE");

    //g.printWithWeight();
    //Dijkstra dijkstra(d.getVecRequest().size());
    //dijkstra.getCostByDijkstra(g.getAdjList(), g.getQtVertex(), 9, 2, 0);

    //g.printWithCost();
    //cout << "Uniform: " << Uniform(0,1) << endl;
    return 0;
    //return EXIT_SUCCESS;
}
