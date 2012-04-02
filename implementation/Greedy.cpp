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
        //MUDAR SEMENTE
        //vecrequest[i].setKey(rand() / static_cast<float>(RAND_MAX));
        vecrequest[i].setKey(rand() / static_cast<float>(Uniform(0,1)));
        //cout << "Nova Chave " << i << ": " << vecrequest[i].getKey() << endl;
    }
    sort(vecrequest.begin(), vecrequest.end(), comparison_request_by_key());
}

void Greedy::DemandSwap(std::vector<Request>& vecrequest)
{
    //cout << "Have 0: " << vecrequest.size() << " - Front: " << vecrequest[0].getSrc() << endl;
    vecrequest.push_back(vecrequest.front());
    //cout << "Have 1: " << vecrequest.size() << " - Front: " << vecrequest[0].getSrc() << endl;
    vecrequest.erase(vecrequest.begin());

    //ObjDijkstra.Paths[vecrequest.size()] = ObjDijkstra.Paths[0];
    //ObjDijkstra.Paths.erase(ObjDijkstra.Paths.begin());

    //cout << "Have 2: " << vecrequest.size() << " - Front: " << vecrequest[0].getSrc() << endl;
    //cout << "Have 3: " << vecrequest.size() << " - Front: " << vecrequest.back().getSrc() << endl;
}

float Greedy::execute(Graph& graph, std::vector<Request>& vecrequest, int qtvertex, bool regenerateDijkstra)
{
    //float telapsed;
    /*time_t t1=time(NULL);
    time_t t2=time(NULL);*/

    //ofstream fout("f:\\greedy_abilene.txt");
    //fout << totalcost << ";";
    //Functions functions;

    if(regenerateDijkstra)
    {
        Dijkstra dijkstra(vecrequest.size());
        ObjDijkstra = dijkstra;
    }

    //while (true)
    //{
//        GeneratePermutation(request);
//        cost = greedy.Execute(request, 5, 100);

    //DemandSort(vecrequest);
    //totalcost = 0;
    //Pegando o custo com dijkstra
    //for(int i=0; i<vecrequest.size(); i++)
    //{
    //primeira execuчуo
    //totalcost = 0;




    for(int p=0; p<vecrequest.size(); p++)
    {
        ObjDijkstra.setAllGraphEdgeIncCost(graph, qtvertex, vecrequest[p].getQt());
        ObjDijkstra.getCostByDijkstra(graph.getAdjList(), qtvertex, vecrequest[p].getSrc(), vecrequest[p].getDst(), p );
        addPath(graph, p, qtvertex, vecrequest[p].getQt());
        //graph.printWithQtRequests();
        //cout << "TOTALCOST: " << totalcost << endl;




        /*for(int i=0; i<qtvertex; i++)
        {
            for(int x=1; x<graph.getAdjList()[i].size(); x++)
            {
                //Custo incremental da aresta
                //graph.getAdjList()[i][x].setIncCost(functions.fwdm(graph.getAdjList()[i][x].getCost() + vecrequest[p].getQt(), graph.getAdjList()[i][x].getWeight()) - functions.fwdm(graph.getAdjList()[i][x].getCost(), graph.getAdjList()[i][x].getWeight()) + graph.getAdjList()[i][x].getCost());
                //cout << "FWDM: " << functions.fwdm(graph.getAdjList()[i][x].getQtRequests() + vecrequest[p].getQt(), graph.getAdjList()[i][x].getWeight()) - functions.fwdm(graph.getAdjList()[i][x].getQtRequests(), graph.getAdjList()[i][x].getWeight()) << endl;
                w = graph.getAdjList()[i][x].getQtRequests();
                l = graph.getAdjList()[i][x].getWeight();
                a = vecrequest[p].getQt();
                inccost = functions.fwdm(w + a, l) - functions.fwdm(w, l);
                graph.getAdjList()[i][x].setIncCost(inccost + graph.getAdjList()[i][x].getCost());
                //cout << "INCOST: " << inccost << endl;
            }

        }

        //Aumentar o custo da rede aqui, custo incremental já ok
        ObjDijkstra.getCostByDijkstra(graph.getAdjList(), qtvertex, vecrequest[p].getSrc(), vecrequest[p].getDst(),p);
        //cout << "Path Size [" << p << "]: " << ObjDijkstra.Paths[p].size() << endl;

        //SETANDO O NOVO CUSTO PARA CADA SEGMENTO COM O CAMINHO DE DIJKSTRA

        for(int q=0; q<ObjDijkstra.Paths[p].size(); q++)
        {
            cout << "ROUTE TO ADD COST - SRC: " << ObjDijkstra.Paths[p][0] << " - DST: " << ObjDijkstra.Paths[p][ObjDijkstra.Paths[p].size() - 1] << endl;
            //totalcost += functions.fwdm(vecrequest[p].getQt(), dijkstra.Paths[p][q].getWeight());

            int r=1;
            //while(r<ObjDijkstra.Paths[p].size())
            while(r<graph.getAdjList()[ObjDijkstra.Paths[p][q]].size())
            {
                if(graph.getAdjList()[ObjDijkstra.Paths[p][q]][r].getNumber() == ObjDijkstra.Paths[p][q+1])
                {
                    //cout << "COST BEFORE: " << "[" << graph.getAdjList()[dijkstra.Paths[p][q]][r].getNumber() << "] --> " << graph.getAdjList()[dijkstra.Paths[p][q]][r].getCost();
                    //graph.getAdjList()[ObjDijkstra.Paths[p][q]][r].setCost(graph.getAdjList()[ObjDijkstra.Paths[p][q]][r].getCost() + graph.getAdjList()[ObjDijkstra.Paths[p][q]][r].getIncCost());
                    //cout << " - COST AFTER: "  << "[" << graph.getAdjList()[dijkstra.Paths[p][q]][r].getNumber() << "] --> " << graph.getAdjList()[dijkstra.Paths[p][q]][r].getCost() << endl;


                    graph.getAdjList()[ObjDijkstra.Paths[p][q]][r].setQtRequests(graph.getAdjList()[ObjDijkstra.Paths[p][q]][r].getQtRequests() + vecrequest[p].getQt());
                    //graph.getAdjList()[ObjDijkstra.Paths[p][q]][r].setQtRequests(2500);


                    //cout << "QTREQUEST : " << graph.getAdjList()[ObjDijkstra.Paths[p][q]][r].getQtRequests() << endl;
                    float w = graph.getAdjList()[ObjDijkstra.Paths[p][q]][r].getQtRequests();
                    float l = graph.getAdjList()[ObjDijkstra.Paths[p][q]][r].getWeight();
                    graph.getAdjList()[ObjDijkstra.Paths[p][q]][r].setCost(functions.fwdm(w, l));
                    //totalcost += graph.getAdjList()[dijkstra.Paths[p][q]][r].getCost();


                    cout << graph.getAdjList()[ObjDijkstra.Paths[p][q]][r].getNumber() << " - ";
                    break;
                }
                r++;
            }

            //graph.getAdjList()[dijkstra.Paths[p][q]][0].setCost(graph.getAdjList()[dijkstra.Paths[p][q]][0].getIncCost());
            //graph.getAdjList()[dijkstra.Paths[p][q]][0].setQtRequests(graph.getAdjList()[dijkstra.Paths[p][q]][0].getQtRequests() + vecrequest[p].getQt());
            //totalcost += graph.getAdjList()[dijkstra.Paths[p][q]][0].getCost();

        }
        cout << endl;

        //SETANDO O NOVO CUSTO PARA CADA SEGMENTO COM O CAMINHO DE DIJKSTRA INVERTIDO
        /*vector<int> path_copy = ObjDijkstra.Paths[p];
        reverse(path_copy.begin(), path_copy.end());
        for(int q=0; q<ObjDijkstra.Paths[p].size(); q++)
        {
            //totalcost += functions.fwdm(vecrequest[p].getQt(), dijkstra.Paths[p][q].getWeight());

            int r=1;
            //while(r<ObjDijkstra.Paths[p].size())
            while(r<graph.getAdjList()[ObjDijkstra.Paths[p][q]].size())
            {
                if(graph.getAdjList()[ObjDijkstra.Paths[p][q]][r].getNumber() == ObjDijkstra.Paths[p][q + 1])
                {
                    //cout << "COST BEFORE: " << "[" << graph.getAdjList()[dijkstra.Paths[p][q]][r].getNumber() << "] --> " << graph.getAdjList()[dijkstra.Paths[p][q]][r].getCost();
                    //graph.getAdjList()[ObjDijkstra.Paths[p][q]][r].setCost(graph.getAdjList()[ObjDijkstra.Paths[p][q]][r].getCost() + graph.getAdjList()[ObjDijkstra.Paths[p][q]][r].getIncCost());
                    //cout << " - COST AFTER: "  << "[" << graph.getAdjList()[dijkstra.Paths[p][q]][r].getNumber() << "] --> " << graph.getAdjList()[dijkstra.Paths[p][q]][r].getCost() << endl;
                    graph.getAdjList()[ObjDijkstra.Paths[p][q]][r].setQtRequests(graph.getAdjList()[ObjDijkstra.Paths[p][q]][r].getQtRequests() + vecrequest[p].getQt());
                    float w = graph.getAdjList()[ObjDijkstra.Paths[p][q]][r].getQtRequests();
                    float l = graph.getAdjList()[ObjDijkstra.Paths[p][q]][r].getWeight();
                    graph.getAdjList()[ObjDijkstra.Paths[p][q]][r].setCost(functions.fwdm(w, l));
                    //totalcost += graph.getAdjList()[dijkstra.Paths[p][q]][r].getCost();
                    break;
                }
                r++;
            }

            //graph.getAdjList()[dijkstra.Paths[p][q]][0].setCost(graph.getAdjList()[dijkstra.Paths[p][q]][0].getIncCost());
            //graph.getAdjList()[dijkstra.Paths[p][q]][0].setQtRequests(graph.getAdjList()[dijkstra.Paths[p][q]][0].getQtRequests() + vecrequest[p].getQt());
            //totalcost += graph.getAdjList()[dijkstra.Paths[p][q]][0].getCost();

        }
        //FIM DO CUSTO REVERSO

        */


        /*if(p==0)
        {
            mincost = totalcost;
        }
        cout << "MinCost: " << mincost << endl;*/

    }

    //cout << "END OF EXECUTE\n\n";

    //graph.printWithCost();
    //graph.printWithIncCost();






    /*float totalcost = 0;
    for(int p = 0; p < qtvertex; p++)
    {
        for(int x = 0; x < graph.getAdjList()[p].size(); x++)
        {
            //cout << "TOTALCOST: " << graph.getAdjList()[p][x].getCost() << endl;
            totalcost += graph.getAdjList()[p][x].getCost();
        }
    }*/






    //}

    /*fout << "totalcost: " << totalcost << ";";
    if (totalcost < mincost)
    {*/
    //mincost = totalcost;
    //}

    /*        t2 = time(NULL);
            // printf("%.4lf\n",telapsed); 10 minutos.
            float totaltime = t2 - t1;

            if(totaltime > timeexec)
            {
                fout.close();
                break;
            }*/

    //Refinamento iterativo

    //DemandSwap(vecrequest);

    //}

    //refine(graph, vecrequest, qtvertex);
    long totalcost = 0;
    for(int p = 0; p < qtvertex; p++)
    {
        for(int x = 1; x < graph.getAdjList()[p].size(); x++)
        {
            //cout << "TOTALCOST: " << graph.getAdjList()[p][x].getCost() << endl;
            totalcost += graph.getAdjList()[p][x].getCost();
        }
    }

    MinCost = totalcost;
    return totalcost;

}

float Greedy::deletePath(Graph& graph, int path, int qtvertex, int qtrequests)
{
    //primeiro vértice
    //float w = graph.getAdjList()[ObjDijkstra.Paths[path][0]][0].getQtRequests();
    //float l = graph.getAdjList()[ObjDijkstra.Paths[path][0]][0].getWeight();
    //float a = qtrequests;
    //float inccost = functions.fwdm(w + a, l) - functions.fwdm(w, l);
    /*graph.getAdjList()[ObjDijkstra.Paths[path][0]][0].setIncCost(graph.getAdjList()[ObjDijkstra.Paths[path][0]][0].getCost() - inccost);
    graph.getAdjList()[ObjDijkstra.Paths[path][0]][0].setCost(graph.getAdjList()[ObjDijkstra.Paths[path][0]][0].getCost() - graph.getAdjList()[ObjDijkstra.Paths[path][0]][0].getIncCost());
    graph.getAdjList()[ObjDijkstra.Paths[path][0]][0].setQtRequests(graph.getAdjList()[ObjDijkstra.Paths[path][0]][0].getQtRequests() - qtrequests);
    *///fim primeiro vértice



    cout << "DIJKSTRA PATH FOR DELETE: ";
    for(int v=0; v<ObjDijkstra.Paths[path].size(); v++)
    {
        cout << ObjDijkstra.Paths[path][v] << " - ";
    }
    cout << endl;

    cout << "DELETED PATH: \n";



    /*for(int q=0; q<ObjDijkstra.Paths[path].size()-1; q++)
    {
        int r=1;
        while(r<graph.getNeighbors(ObjDijkstra.Paths[path][q]).size())
        //while(true)
        {
            //if( (graph.getAdjList()[ObjDijkstra.Paths[path][q]][r].getNumber() == ObjDijkstra.Paths[path][q+1]) && (q<ObjDijkstra.Paths[path].size() - 1) )
            if((graph.getNeighbors(ObjDijkstra.Paths[path][q])[r].getNumber() == ObjDijkstra.Paths[path][q + 1]) && (q<graph.getNeighbors(ObjDijkstra.Paths[path][q]).size()))
            {
                //graph.getAdjList()[ObjDijkstra.Paths[path][q]][r].setQtRequests(graph.getAdjList()[ObjDijkstra.Paths[path][q]][r].getQtRequests() - qtrequests);
                //cout << "REQUESTS - Edge: " <<  graph.getAdjList()[ObjDijkstra.Paths[path][q]][r].getQtRequests() << " - QTRequests: " << qtrequests;
                graph.getAdjList()[ObjDijkstra.Paths[path][q]][r].setQtRequests(graph.getAdjList()[ObjDijkstra.Paths[path][q]][r].getQtRequests() - qtrequests);


                cout << graph.getAdjList()[ObjDijkstra.Paths[path][q]][r].getNumber() << " - ";


                //cout << " - New EdgeQTRequests: " <<  graph.getAdjList()[ObjDijkstra.Paths[path][q]][r].getQtRequests() << endl;
                float w = graph.getAdjList()[ObjDijkstra.Paths[path][q]][r].getQtRequests();
                float l = graph.getAdjList()[ObjDijkstra.Paths[path][q]][r].getWeight();
                graph.getAdjList()[ObjDijkstra.Paths[path][q]][r].setCost(functions.fwdm(w, l));
                //totalcost += graph.getAdjList()[dijkstra.Paths[p][q]][r].getCost();
                break;
            }
            r++;
        }
    }*/

    vector<int> path_cp = ObjDijkstra.Paths[path];
    for(int i=0; i<path_cp.size() - 1; i++)
    {
        int z = path_cp[i], zprox = path_cp[i + 1], x = 1;
        while(x<graph.getNeighbors(z).size())
        {
            //if(i < graph.getNeighbors(path_cp[i]).size() - 1)
            //{
            if(graph.getNeighbors(z)[x].getNumber() == zprox)
            {
                graph.getNeighbors(z)[x].setQtRequests(graph.getNeighbors(z)[x].getQtRequests() - qtrequests);
                float w = graph.getNeighbors(z)[x].getQtRequests();
                int l = graph.getNeighbors(z)[x].getWeight();
                graph.getNeighbors(z)[x].setCost(functions.fwdm(w, l));
                cout << "Deleting: " << graph.getNeighbors(z)[x].getNumber() << " - Path_CP: Z: " << z << " - Path_CP: ZPROX: " << zprox << " - Qt:" << qtrequests << endl;
                //break;
            }
            /*}else{
                break;
            }*/
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
    //primeiro vértice
    //float w = graph.getAdjList()[ObjDijkstra.Paths[path][0]][0].getQtRequests();
    //float l = graph.getAdjList()[ObjDijkstra.Paths[path][0]][0].getWeight();
    //float a = qtrequests;
    //float inccost = functions.fwdm(w + a, l) - functions.fwdm(w, l);
    /*graph.getAdjList()[ObjDijkstra.Paths[path][0]][0].setIncCost(graph.getAdjList()[ObjDijkstra.Paths[path][0]][0].getCost() - inccost);
    graph.getAdjList()[ObjDijkstra.Paths[path][0]][0].setCost(graph.getAdjList()[ObjDijkstra.Paths[path][0]][0].getCost() - graph.getAdjList()[ObjDijkstra.Paths[path][0]][0].getIncCost());
    graph.getAdjList()[ObjDijkstra.Paths[path][0]][0].setQtRequests(graph.getAdjList()[ObjDijkstra.Paths[path][0]][0].getQtRequests() - qtrequests);
    *///fim primeiro vértice



    cout << "DIJKSTRA PATH FOR ADD: ";
    for(int v=0; v<ObjDijkstra.Paths[path].size(); v++)
    {
        cout << ObjDijkstra.Paths[path][v] << " - ";
    }
    cout << endl;

    cout << "ADDED PATH: \n";



    /*for(int q=0; q<ObjDijkstra.Paths[path].size()-1; q++)
    {
        int r=1;
        while(r<graph.getNeighbors(ObjDijkstra.Paths[path][q]).size())
        //while(true)
        {
            //if( (graph.getAdjList()[ObjDijkstra.Paths[path][q]][r].getNumber() == ObjDijkstra.Paths[path][q+1]) && (q<ObjDijkstra.Paths[path].size() - 1) )
            if((graph.getNeighbors(ObjDijkstra.Paths[path][q])[r].getNumber() == ObjDijkstra.Paths[path][q + 1]) && (q<graph.getNeighbors(ObjDijkstra.Paths[path][q]).size()))
            {
                //graph.getAdjList()[ObjDijkstra.Paths[path][q]][r].setQtRequests(graph.getAdjList()[ObjDijkstra.Paths[path][q]][r].getQtRequests() - qtrequests);
                //cout << "REQUESTS - Edge: " <<  graph.getAdjList()[ObjDijkstra.Paths[path][q]][r].getQtRequests() << " - QTRequests: " << qtrequests;
                graph.getAdjList()[ObjDijkstra.Paths[path][q]][r].setQtRequests(graph.getAdjList()[ObjDijkstra.Paths[path][q]][r].getQtRequests() + qtrequests);


                cout << graph.getAdjList()[ObjDijkstra.Paths[path][q]][r].getNumber() << " - ";


                //cout << " - New EdgeQTRequests: " <<  graph.getAdjList()[ObjDijkstra.Paths[path][q]][r].getQtRequests() << endl;
                float w = graph.getAdjList()[ObjDijkstra.Paths[path][q]][r].getQtRequests();
                float l = graph.getAdjList()[ObjDijkstra.Paths[path][q]][r].getWeight();
                graph.getAdjList()[ObjDijkstra.Paths[path][q]][r].setCost(functions.fwdm(w, l));
                //totalcost += graph.getAdjList()[dijkstra.Paths[p][q]][r].getCost();
                break;
            }
            r++;
        }
    }*/

    vector<int> path_cp = ObjDijkstra.Paths[path];
    for(int i=0; i<path_cp.size() - 1; i++)
    {
        int z = path_cp[i], zprox = path_cp[i + 1], x = 1;
        while(x<graph.getNeighbors(z).size())
        {
            //if(i < graph.getNeighbors(path_cp[i]).size() - 1)
            //{
            if(graph.getNeighbors(z)[x].getNumber() == zprox)
            {
                graph.getNeighbors(z)[x].setQtRequests(graph.getNeighbors(z)[x].getQtRequests() + qtrequests);
                float w = graph.getNeighbors(z)[x].getQtRequests();
                float l = graph.getNeighbors(z)[x].getWeight();
                graph.getNeighbors(z)[x].setCost(functions.fwdm(w, l));
                cout << "Adding: " << graph.getNeighbors(z)[x].getNumber() << " - Path_CP: Z: " << z << " - Path_CP: ZPROX: " << zprox << " - Qt:" << qtrequests << " - NEW COST: " << graph.getNeighbors(z)[x].getCost() << " - FWDM(w,l): " << functions.fwdm(w, l) << " - w: " << w << " - l: " << l << endl;
                //break;
            }
            /*}else{
                break;
            }*/
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
    cout << endl << "Custo execute without refinement:::::: " << act<< endl;

    int actrequest = 0, path_ch = 0, min_cost_ch = 0;
    vector<int> actpath;

    //float prev_mincos = MinCost;
    system("PAUSE");


    //com actrequest = 0 ao ser declarado forço a primeira execução do loop while
    while((path_ch > 0) || (min_cost_ch > 0) || (actrequest < vecrequest.size()))
    {
        path_ch = 0;
        min_cost_ch = 0;

        act = deletePath(graph, 0, qtvertex, vecrequest[0].getQt());
        DemandSwap(vecrequest);
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

            actpath = ObjDijkstra.Paths[i];
            deletePath(graph, i, qtvertex, vecrequest[i].getQt());
            ObjDijkstra.setAllGraphEdgeIncCost(graph, qtvertex, vecrequest[i].getQt());
            ObjDijkstra.getCostByDijkstra(graph.getAdjList(), qtvertex, vecrequest[i].getSrc(), vecrequest[i].getDst(), i);
            cout << "AFTER ADD PATH THE COST IS: ";

            act = addPath(graph, i, qtvertex, vecrequest[i].getQt());

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
