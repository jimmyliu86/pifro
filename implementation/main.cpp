#include <cstdlib>
#include <iostream>



#include "Vertex.h"
#include "Graph.h"
#include "Demand.h"
#include "Dijkstra.h"
#include "./Greedy.h"
#include "./rvgs.h"

using namespace std;

int main(int argc, char *argv[])
{

    //Vertex v(1,0,123223.9880);
    //v.print();
    //Vertex tmp(2,0,0);
    //Vertex tmp2(1,0,0);


    Graph g("abilene.net",0);
    //g.loadFromSNDFile("abilene.net");
    //g.addEdge(2,1);
    g.printWithWeight();

    cout << endl << endl;

    Demand d("abilene.trf",0, g.getAdjList(), g.getQtVertex());
    //d.print();

    //Dijkstra dij;
    //float x = dij.getCostByDijkstra(g.getAdjList(), g.getQtVertex(), 1, 2);
    //cout << "Custo Dijkstra: " << x << endl;

    Greedy greedy;
    cout.precision(10);
    cout << "\n\n\nCUSTO DO GREEDY: " << greedy.execute(g.getAdjList(), d.getVecRequest(), g.getQtVertex(), 10) << endl;

    cout << "Uniform: " << Uniform(0,1) << endl;
    return 0;
    //return EXIT_SUCCESS;
}
