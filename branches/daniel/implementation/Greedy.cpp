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

void Greedy::setObjDijkstra(Dijkstra& objdijkstra)
{
  ObjDijkstra = objdijkstra;
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
  for(int i=0; i<vecrequest.size(); i++) {
    vecrequest[i].setKey(rand() / static_cast<float>(Uniform(0,1)));
  }
  sort(vecrequest.begin(), vecrequest.end(), comparision_request_by_key());
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
  if(regenerateDijkstra) {
    //Dijkstra dijkstra(vecrequest.size());
    ObjDijkstra.Paths.clear();
    ObjDijkstra.Paths.resize(vecrequest.size());
    //ObjDijkstra = dijkstra;
  }

  for(int p=0; p<vecrequest.size(); p++) {
    ObjDijkstra.setAllGraphEdgeIncCost(graph, qtvertex, vecrequest[p].getQt());
    ObjDijkstra.getCostByDijkstra(graph.getAdjList(), qtvertex, vecrequest[p].getSrc(), vecrequest[p].getDst(), p );
    addPath(graph, p, qtvertex, vecrequest[p].getQt());
    //cout << "AQUI: " << p << endl;
  }

  //refine(graph, vecrequest, qtvertex);
  float totalcost = graph.getTotalCost();
  /*for(int p = 0; p < qtvertex; p++)
  {
      for(int x = 1; x < graph.getAdjList()[p].size(); x++)
      {
          totalcost += graph.getAdjList()[p][x].getCost();
      }
  }*/

  //MinCost = totalcost;
  //graph.printWithQtRequests();
  return totalcost;

}

float Greedy::deletePath(Graph& graph, int path, int qtvertex, int qtrequests)
{


  /*cout << "DIJKSTRA PATH FOR ADD: ";
  for(int v=0; v<ObjDijkstra.Paths[path].size(); v++)
  {
      cout << ObjDijkstra.Paths[path][v] << " - ";
  }
  cout << endl;*/

  //cout << "DELETED PATH: \n";

  vector<int> path_cp = ObjDijkstra.Paths[path];
  for(int i=0; i<path_cp.size() - 1; i++) {
    int z = path_cp[i], zprox = path_cp[i + 1], x = 1;
    while(x<graph.getNeighbors(z).size()) {
      if(graph.getNeighbors(z)[x].getNumber() == zprox) {
        graph.getNeighbors(z)[x].setQtRequests(graph.getNeighbors(z)[x].getQtRequests() - qtrequests);
        int w = graph.getNeighbors(z)[x].getQtRequests();
        float l = graph.getNeighbors(z)[x].getWeight();
        graph.getNeighbors(z)[x].setCost(functions.fwdm(w, l));
        //cout << "Deleting: " << graph.getNeighbors(z)[x].getNumber() << " - Path_CP: Z: " << z << " - Path_CP: ZPROX: " << zprox << " - Qt:" << qtrequests << endl;
        break;
      }
      x++;
    }
  }

  for(int i=path_cp.size() - 1; i >= 0; i--) {
    int z = path_cp[i], zprev = path_cp[i - 1], x = graph.getNeighbors(z).size() - 1;
    while(x >= 1) {
      if(graph.getNeighbors(z)[x].getNumber() == zprev) {
        graph.getNeighbors(z)[x].setQtRequests(graph.getNeighbors(z)[x].getQtRequests() - qtrequests);
        int w = graph.getNeighbors(z)[x].getQtRequests();
        float l = graph.getNeighbors(z)[x].getWeight();
        graph.getNeighbors(z)[x].setCost(functions.fwdm(w, l));
        //cout << "Deleting: " << graph.getNeighbors(z)[x].getNumber() << " - Path_CP: Z: " << z << " - Path_CP: ZPROX: " << zprox << " - Qt:" << qtrequests << endl;
        break;
      }
      x--;
    }
  }

   //cout << endl << endl;
   //graph.printWithQtRequests();
   //system("PAUSE");
  /*float totalcost = 0;
  for(int p = 0; p < qtvertex; p++)
  {
      for(int x = 1; x < graph.getAdjList()[p].size(); x++)
      {
          //cout << "TOTALCOST: " << graph.getAdjList()[p][x].getCost() << endl;
          totalcost += graph.getAdjList()[p][x].getCost();
      }
  }

  //return totalcost;*/
  float totalcost = graph.getTotalCost();
  if(totalcost < 0) {
    cout << "Negative Actual Cost found: \n";
    graph.printWithQtRequests();
    cout << "DIJKSTRA PATH FOR ADD: \n";
    for(int v=0; v<ObjDijkstra.Paths[path].size(); v++) {
      cout << ObjDijkstra.Paths[path][v] << " - ";
    }
    cout << endl;
    system("PAUSE");
  }
  return totalcost;

}


float Greedy::addPath(Graph& graph, int path, int qtvertex, int qtrequests)
{

  /*cout << "DIJKSTRA PATH FOR ADD: ";
  for(int v=0; v<ObjDijkstra.Paths[path].size(); v++)
  {
      cout << ObjDijkstra.Paths[path][v] << " - ";
  }
  cout << endl;*/

  //cout << "DELETED PATH: \n";

  vector<int> path_cp = ObjDijkstra.Paths[path];
  for(int i=0; i<path_cp.size() - 1; i++) {
    int z = path_cp[i], zprox = path_cp[i + 1], x = 1;
    while(x<graph.getNeighbors(z).size()) {
      if(graph.getNeighbors(z)[x].getNumber() == zprox) {
        graph.getNeighbors(z)[x].setQtRequests(graph.getNeighbors(z)[x].getQtRequests() + qtrequests);
        int w = graph.getNeighbors(z)[x].getQtRequests();
        float l = graph.getNeighbors(z)[x].getWeight();
        graph.getNeighbors(z)[x].setCost(functions.fwdm(w, l));
        //cout << "Deleting: " << graph.getNeighbors(z)[x].getNumber() << " - Path_CP: Z: " << z << " - Path_CP: ZPROX: " << zprox << " - Qt:" << qtrequests << endl;
        break;
      }
      x++;
    }
  }

  for(int i=path_cp.size() - 1; i >= 0; i--) {
    int z = path_cp[i], zprev = path_cp[i - 1], x = graph.getNeighbors(z).size() - 1;
    while(x >= 1) {
      if(graph.getNeighbors(z)[x].getNumber() == zprev) {
        graph.getNeighbors(z)[x].setQtRequests(graph.getNeighbors(z)[x].getQtRequests() + qtrequests);
        int w = graph.getNeighbors(z)[x].getQtRequests();
        float l = graph.getNeighbors(z)[x].getWeight();
        graph.getNeighbors(z)[x].setCost(functions.fwdm(w, l));
        //cout << "Deleting: " << graph.getNeighbors(z)[x].getNumber() << " - Path_CP: Z: " << z << " - Path_CP: ZPROX: " << zprox << " - Qt:" << qtrequests << endl;
        break;
      }
      x--;
    }
  }

   //cout << endl << endl;
   //graph.printWithQtRequests();
   //system("PAUSE");
  /*float totalcost = 0;
  for(int p = 0; p < qtvertex; p++)
  {
      for(int x = 1; x < graph.getAdjList()[p].size(); x++)
      {
          //cout << "TOTALCOST: " << graph.getAdjList()[p][x].getCost() << endl;
          totalcost += graph.getAdjList()[p][x].getCost();
      }
  }

  //return totalcost;*/
  float totalcost = graph.getTotalCost();
  if(totalcost < 0) {
    cout << "Negative Actual Cost found: \n";
    graph.printWithQtRequests();
    cout << "DIJKSTRA PATH FOR ADD: \n";
    for(int v=0; v<ObjDijkstra.Paths[path].size(); v++) {
      cout << ObjDijkstra.Paths[path][v] << " - ";
    }
    cout << endl;
    system("PAUSE");
  }
  return totalcost;

}


float Greedy::executeWithRefine(Graph& graph, std::vector<Request>& vecrequest)
{
  float act = 0;
  graph.cleanCosts();
  act = execute(graph, vecrequest, graph.getQtVertex(), true);
  this->MinCost = act;

  int actrequest = -1, path_ch = 1, min_cost_ch = 0, lastalt = -2, loops = 0;
  vector<int> actpath;

  while(((path_ch > 0) || (min_cost_ch > 0) || (loops < 1)) && (lastalt != actrequest)) {

    if((lastalt == actrequest) && (loops > 0))
    {
      break;
    }

    if(actrequest == vecrequest.size() -1)
    {
      actrequest = -1;
      loops++;
    }

    actrequest++;

    path_ch = 0;
    min_cost_ch = 0;

    for(int i=0; i<vecrequest.size(); i++) {

      //Resolvendo o problema da última rota excluída e novamente adicionada
      actpath.clear();
      actpath = ObjDijkstra.Paths[i];

      deletePath(graph, i, graph.getQtVertex(), vecrequest[i].getQt());
      ObjDijkstra.setAllGraphEdgeIncCost(graph, graph.getQtVertex(), vecrequest[i].getQt());
      ObjDijkstra.getCostByDijkstra(graph.getAdjList(), graph.getQtVertex(), vecrequest[i].getSrc(), vecrequest[i].getDst(), i);
      act = addPath(graph, i, graph.getQtVertex(), vecrequest[i].getQt());

      if(act < MinCost) {
        MinCost = act;
        min_cost_ch++;
        lastalt = i;
        continue;
      }

      int u = 0;
      if(path_ch == 0) {
        while(u < actpath.size()) {
          if(actpath[u] != ObjDijkstra.Paths[i][u]) {
            path_ch++;
            lastalt = i;
            break;
          }
          u++;
        }
      }
    }

  }

  return MinCost;
}


float Greedy::executeWithRefine(Graph graph, std::vector<Request> vecrequest, std::vector<int> permutation)
{
  std::vector<Request> aux;
  aux.resize(vecrequest.size());

  for(int i=0; i<permutation.size(); i++) {
    aux.push_back(vecrequest[permutation[i]]);
  }

  float act = 0;
  graph.cleanCosts();
  act = execute(graph, aux, graph.getQtVertex(), true);

  MinCost = act;

  int actrequest = -1, path_ch = 1, min_cost_ch = 0, lastalt = -2, loops = 0;
  vector<int> actpath;

  //com actrequest = 0 ao ser declarado forço a primeira execução do loop while
  //while(((path_ch > 0) || (min_cost_ch > 0)) || (actrequest < aux.size())) {
  while(((path_ch > 0) || (min_cost_ch > 0) || (loops < 1)) && (lastalt != actrequest)) {


    //act = deletePath(graph, 0, graph.getQtVertex(), aux[0].getQt());

    //DemandSwap(aux);
    if((lastalt == actrequest) && (loops > 0))
    {
      break;
    }

    if(actrequest == aux.size() -1)
    {
      actrequest = -1;
      loops++;
    }

    actrequest++;

    path_ch = 0;
    min_cost_ch = 0;

    for(int i=0; i<aux.size(); i++) {

      //Resolvendo o problema da última rota excluída e novamente adicionada
      actpath.clear();
      actpath = ObjDijkstra.Paths[i];
      /*if(i < aux.size() - 1)
      {*/

      deletePath(graph, i, graph.getQtVertex(), aux[i].getQt());
      ObjDijkstra.setAllGraphEdgeIncCost(graph, graph.getQtVertex(), aux[i].getQt());
      ObjDijkstra.getCostByDijkstra(graph.getAdjList(), graph.getQtVertex(), aux[i].getSrc(), aux[i].getDst(), i);
      act = addPath(graph, i, graph.getQtVertex(), aux[i].getQt());

      if(act < MinCost) {
        MinCost = act;
        min_cost_ch++;
        lastalt = i;
        continue;
      }
      /*}
      else
      {
          ObjDijkstra.setAllGraphEdgeIncCost(graph, graph.getQtVertex(), aux[i].getQt());
          ObjDijkstra.getCostByDijkstra(graph.getAdjList(), graph.getQtVertex(), aux[i].getSrc(), aux[i].getDst(), i);
          act = addPath(graph, i, graph.getQtVertex(), aux[i].getQt());
      }*/




      int u = 0;
      if(path_ch == 0) {
        while(u < actpath.size()) {
          if(actpath[u] != ObjDijkstra.Paths[i][u]) {
            path_ch++;
            lastalt = i;
            break;
          }
          u++;
        }
      }
    }

  }

  return MinCost;
}
