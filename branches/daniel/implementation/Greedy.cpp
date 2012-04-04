#include "./Greedy.h"


Greedy::Greedy()
{
}

Greedy::Greedy(int qtRequests)
{
    Dijkstra tmp(qtRequests);
    ObjDijkstra = tmp;
}

void Greedy::setGDemand(Demand& demand)
{
    GDemand = demand;
    Dijkstra dijkstra(demand.getVecRequest().size());
    ObjDijkstra = dijkstra;
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
        vecrequest[i].setKey(rand() / static_cast<float>(Uniform(0,1)));
    }
    sort(vecrequest.begin(), vecrequest.end(), comparison_request_by_key());
}

void Greedy::DemandSwap(std::vector<Request>& vecrequest)
{
    vecrequest.push_back(vecrequest[0]);
    vecrequest.erase(vecrequest.begin());

    ObjDijkstra.Paths.push_back(ObjDijkstra.Paths[0]);
    ObjDijkstra.Paths.erase(ObjDijkstra.Paths.begin());

}

float Greedy::execute(Graph& graph, std::vector<Request>& vecrequest, int qtvertex, bool regenerateDijkstra)
{
    if(regenerateDijkstra)
    {
        Dijkstra dijkstra(vecrequest.size());
        ObjDijkstra = dijkstra;
    }

    for(int p=0; p<vecrequest.size(); p++)
    {
        ObjDijkstra.setAllGraphEdgeIncCost(graph, qtvertex, vecrequest[p].getQt());
        ObjDijkstra.getCostByDijkstra(graph.getAdjList(), qtvertex, vecrequest[p].getSrc(), vecrequest[p].getDst(), p );
        addPath(graph, p, qtvertex, vecrequest[p].getQt());
    }

    //refine(graph, vecrequest, qtvertex);
    long totalcost = 0;
    for(int p = 0; p < qtvertex; p++)
    {
        for(int x = 1; x < graph.getAdjList()[p].size(); x++)
        {
            totalcost += graph.getAdjList()[p][x].getCost();
        }
    }

    MinCost = totalcost;
    return totalcost;

}

float Greedy::deletePath(Graph& graph, int path, int qtvertex, int qtrequests)
{

    cout << "DIJKSTRA PATH FOR DELETE: ";
    for(int v=0; v<ObjDijkstra.Paths[path].size(); v++)
    {
        cout << ObjDijkstra.Paths[path][v] << " - ";
    }
    cout << endl;

    cout << "DELETED PATH: \n";

    vector<int> path_cp = ObjDijkstra.Paths[path];
    for(int i=0; i<path_cp.size() - 1; i++)
    {
        int z = path_cp[i], zprox = path_cp[i + 1], x = 1;
        while(x<graph.getNeighbors(z).size())
        {
            if(graph.getNeighbors(z)[x].getNumber() == zprox)
            {
                graph.getNeighbors(z)[x].setQtRequests(graph.getNeighbors(z)[x].getQtRequests() - qtrequests);
                int w = graph.getNeighbors(z)[x].getQtRequests();
                float l = graph.getNeighbors(z)[x].getWeight();
                graph.getNeighbors(z)[x].setCost(functions.fwdm(w, l));
                cout << "Deleting: " << graph.getNeighbors(z)[x].getNumber() << " - Path_CP: Z: " << z << " - Path_CP: ZPROX: " << zprox << " - Qt:" << qtrequests << endl;
                break;
            }
            x++;
        }
    }



    cout << endl << endl;
    graph.printWithQtRequests();

    float totalcost = 0;
    for(int p = 0; p < qtvertex; p++)
    {
        for(int x = 1; x < graph.getAdjList()[p].size(); x++)
        {
            //cout << "TOTALCOST: " << graph.getAdjList()[p][x].getCost() << endl;
            totalcost += graph.getAdjList()[p][x].getCost();
        }
    }

    return totalcost;
}


float Greedy::addPath(Graph& graph, int path, int qtvertex, int qtrequests)
{
    cout << "DIJKSTRA PATH FOR ADD: ";
    for(int v=0; v<ObjDijkstra.Paths[path].size(); v++)
    {
        cout << ObjDijkstra.Paths[path][v] << " - ";
    }
    cout << endl;

    cout << "ADDED PATH: \n";

    vector<int> path_cp = ObjDijkstra.Paths[path];
    for(int i=0; i<path_cp.size() - 1; i++)
    {
        int z = path_cp[i], zprox = path_cp[i + 1], x = 1;
        while(x<graph.getNeighbors(z).size())
        {
            if(graph.getNeighbors(z)[x].getNumber() == zprox)
            {
                graph.getNeighbors(z)[x].setQtRequests(graph.getNeighbors(z)[x].getQtRequests() + qtrequests);
                int w = graph.getNeighbors(z)[x].getQtRequests();
                float l = graph.getNeighbors(z)[x].getWeight();
                graph.getNeighbors(z)[x].setCost(functions.fwdm(w, l));
                cout << "Adding: " << graph.getNeighbors(z)[x].getNumber() << " - Path_CP: Z: " << z << " - Path_CP: ZPROX: " << zprox << " - Qt:" << qtrequests << " - NEW COST: " << graph.getNeighbors(z)[x].getCost() << " - FWDM(w,l): " << functions.fwdm(w, l) << " - w: " << w << " - l: " << l << endl;
                break;
            }
            x++;
        }
    }


    cout << endl << endl;
    graph.printWithQtRequests();

    float totalcost = 0;
    for(int p = 0; p < qtvertex; p++)
    {
        for(int x = 1; x < graph.getAdjList()[p].size(); x++)
        {
            //cout << "TOTALCOST: " << graph.getAdjList()[p][x].getCost() << endl;
            totalcost += graph.getAdjList()[p][x].getCost();
        }
    }

    return totalcost;
}


float Greedy::executeWithRefine(Graph& graph, std::vector<Request>& vecrequest, int qtvertex,  bool regenerateDijkstra)
{
    float act = 0;
    act = execute(graph, vecrequest, qtvertex, true);
    MinCost = act;
    graph.printWithQtRequests();
    cout << endl << "Cost execute without refinement:::::: " << act<< endl;

    int actrequest = 0, path_ch = 1, min_cost_ch = 0;
    vector<int> actpath;

    //float prev_mincos = MinCost;
    system("PAUSE");

    cout << "Original PATHS: ";
    for(int x = 0; x < vecrequest.size(); x++)
    {

        for(int i = 0; i < ObjDijkstra.Paths[x].size(); i++)
            cout << ObjDijkstra.Paths[x][i] << " - ";

        cout << endl;
    }


    //com actrequest = 0 ao ser declarado forço a primeira execução do loop while
    while(((path_ch > 0) || (min_cost_ch > 0)) || (actrequest < vecrequest.size()))
    //while((path_ch > 0) || (min_cost_ch > 0))
    //while(actrequest < vecrequest.size())
    {
        path_ch = 0;
        min_cost_ch = 0;

        act = deletePath(graph, 0, qtvertex, vecrequest[0].getQt());

        /*cout << "PATH BEFORE: ";
        for(int i = 0; i < ObjDijkstra.Paths[0].size(); i++)
            cout << ObjDijkstra.Paths[0][i] << " - ";
        cout << endl;*/

        DemandSwap(vecrequest);

        /*cout << "PATH AFTER: ";
        for(int i = 0; i < ObjDijkstra.Paths[0].size(); i++)
            cout << ObjDijkstra.Paths[0][i] << " - ";
        cout << endl;*/
        //system("PAUSE");

        //cout << "Aqui";
        actrequest++;
        //cout << "AFTER DELETE PATH THE COST IS: ";
        //cout << act << endl;
        //graph.printWithQtRequests();
        //getCostByDijkstra(std::vector<Vertex>*& adjlist, int qtvertex, int src, int dst, int idpath);
        for(int i=0; i<vecrequest.size(); i++)
        {

            /*cout << "GRAPH WITH TOTAL COST: " << endl;
            graph.printWithQtRequests();
            cout << "\n\nPATH TO DELETE: ";
            for(int u=0; u<ObjDijkstra.Paths[i].size(); u++)
            {
                cout << ObjDijkstra.Paths[i][u] << " - ";
            }
            cout <<  endl;*/



            //Resolvendo o problema da última rota excluída e novamente adicionada
            actpath.clear();
            actpath = ObjDijkstra.Paths[i];
            if(i == vecrequest.size() - 1)
            {
                ObjDijkstra.setAllGraphEdgeIncCost(graph, qtvertex, vecrequest[i].getQt());
                ObjDijkstra.getCostByDijkstra(graph.getAdjList(), qtvertex, vecrequest[i].getSrc(), vecrequest[i].getDst(), i);
                act = addPath(graph, i, qtvertex, vecrequest[i].getQt());
            }
            else
            {
                //actpath.clear();
                //actpath = ObjDijkstra.Paths[i];
                deletePath(graph, i, qtvertex, vecrequest[i].getQt());
                ObjDijkstra.setAllGraphEdgeIncCost(graph, qtvertex, vecrequest[i].getQt());
                ObjDijkstra.getCostByDijkstra(graph.getAdjList(), qtvertex, vecrequest[i].getSrc(), vecrequest[i].getDst(), i);
                cout << "AFTER ADD PATH THE COST IS: ";

                act = addPath(graph, i, qtvertex, vecrequest[i].getQt());
            }




            int u = 0;
            if(path_ch == 0)
            {
                while(u < actpath.size())
                {
                    if(actpath[u] != ObjDijkstra.Paths[i][u])
                    {
                        path_ch++;
                        break;
                    }
                    u++;
                }
            }
            //DemandSwap(vecrequest);
            //graph.printWithQtRequests();
            cout << "\nCOST OF THIS NETWORK: " << act << endl;

            //cout << "GRAPH WITH ADD COST: " << endl;
            //graph.printWithQtRequests();
            //cout << "\n\n\n";
        }

        if(act < MinCost)
        {
            MinCost = act;
            min_cost_ch++;
        }
    }
    return MinCost;
}
