#include "./Greedy.h"


Greedy::Greedy()
{
}


void Greedy::setGDemand(Demand& demand)
{
    GDemand = demand;
}

void Greedy::setGGraph(Graph& graph)
{
    GGraph = graph;
}

Demand Greedy::getGDemand()
{
    return GDemand;
}

Graph Greedy::getGGraph()
{
    return GGraph;
}

void Greedy::DemandSort(std::vector<Request>& vecrequest)
{
    for(int i=0; i<vecrequest.size(); i++)
    {
        //MUDAR SEMENTE
        //vecrequest[i].setKey(rand() / static_cast<float>(RAND_MAX));
        vecrequest[i].setKey(rand() / static_cast<float>(Uniform(0,1)));
        //cout << "Nova Chave " << i << ": " << vecrequest[i].getKey() << endl;
    }
    sort(vecrequest.begin(), vecrequest.end(), comparison_request_by_key());
}

float Greedy::execute(std::vector<Vertex>*& adjlist, std::vector<Request>& vecrequest, int qtvertex, int timeexec)
{
    float telapsed, totalcost;
    double cost, mincost;

    time_t t1=time(NULL);
    time_t t2=time(NULL);

    ofstream fout("f:\\greedy_abilene.txt");
    fout << totalcost << ";";
    Functions functions;
    Dijkstra dijkstra(vecrequest.size());

    while (true)
    {
//        GeneratePermutation(request);
//        cost = greedy.Execute(request, 5, 100);

        DemandSort(vecrequest);
        totalcost = 0;
        //Pegando o custo com dijkstra
        //for(int i=0; i<vecrequest.size(); i++)
        //{
            //primeira execuчуo
            totalcost = 0;
            for(int p=0; p<vecrequest.size(); p++)
            {
                for(int i=0; i<qtvertex; i++)
                {
                    for(int x=0; x<adjlist[i].size(); x++)
                    {
                        //Custo incremental da aresta
                        adjlist[i][x].setIncCost(functions.fwdm(adjlist[i][x].getCost() + vecrequest[p].getQt(), adjlist[i][x].getWeight()) - functions.fwdm(adjlist[i][x].getCost(), adjlist[i][x].getWeight()));
                    }

                }
                //Aumentar o custo da rede aqui, custo incremental já ok
             totalcost += dijkstra.getCostByDijkstra(adjlist, qtvertex, vecrequest[p].getSrc(), vecrequest[p].getDst(),p);
             if(p==0)
             {
                 mincost = totalcost;
             }
             cout << "MinCost: " << mincost << endl;
            }
        //}

        fout << "totalcost: " << totalcost << ";";
        if (totalcost < mincost)
        {
            mincost = totalcost;
        }

        t2 = time(NULL);
        // printf("%.4lf\n",telapsed); 10 minutos.
        float totaltime = t2 - t1;

        if(totaltime > timeexec)
        {
            fout.close();
            break;
        }
    }
    return mincost;

}
