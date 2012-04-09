#include <cstdlib>
#include <iostream>


#include <time.h>
#include "Vertex.h"
#include "Graph.h"
#include "Demand.h"
#include "Dijkstra.h"
#include "Greedy.h"
#include "rvgs.h"

#include "BRKGA.h"

using namespace std;

int main(int argc, char *argv[])
{

    //Vertex v(1,0,123223.9880);
    //v.print();
    //Vertex tmp(2,0,0);
    //Vertex tmp2(1,0,0);
    time_t t2 = time(NULL);
    cout << "T2: " << t2 << endl;

    cout.precision(100);

    Graph g("f:/instance1/atlanta/atlanta.net",0);
    //g.loadFromSNDFile("abilene.net");
    //g.addEdge(2,1);
    g.printWithWeight();
    g.printWithCost();
    g.printWithQtRequests();

    cout << endl << endl;

    Demand d("f:/instance1/atlanta/atlanta.trf",0, g.getAdjList(), g.getQtVertex());
    //d.print();

    //Dijkstra dij;
    //float x = dij.getCostByDijkstra(g.getAdjList(), g.getQtVertex(), 1, 2);
    //cout << "Custo Dijkstra: " << x << endl;

    Greedy greedy;
    //cout.precision(50);
    cout << "\n\n\nGREEDY COST: US$ " << (greedy.executeWithRefine(g, d.getVecRequest())) / 1000000 << endl;
    g.printWithQtRequests();
    //system("PAUSE");






    Graph g2("f:/instance1/atlanta/atlanta.net",0);
    Demand d2("f:/instance1/atlanta/atlanta.trf",0, g.getAdjList(), g.getQtVertex());
    BRKGA ga(100, 20, 70, 10, 0.70f, d.getVecRequest(), g);
    cout << "Best Fitness for BRKGAWithGreedy: US$ " << ga.ExecuteWithGreedy(600) / 1000000 << endl;
    system("PAUSE");

    //g.printWithWeight();
    //Dijkstra dijkstra(d.getVecRequest().size());
    //dijkstra.getCostByDijkstra(g.getAdjList(), g.getQtVertex(), 9, 2, 0);

    //g.printWithCost();
    //cout << "Uniform: " << Uniform(0,1) << endl;
    return 0;
    //return EXIT_SUCCESS;
}
