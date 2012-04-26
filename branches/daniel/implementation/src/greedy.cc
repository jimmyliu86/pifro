// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#include <algorithm>
#include <vector>

#include "./greedy.h"

Greedy::Greedy() {
}

Greedy::Greedy(int qtRequests) {
  Dijkstra tmp(qtRequests);
  dijkstra_ = tmp;
}

void Greedy::SetDemand(Demand& demand) {
  demand_ = demand;
  Dijkstra dijkstra(demand.GetVecRequest().size());
  dijkstra_ = dijkstra;
}

void Greedy::SetGraph(Graph& graph) {
  graph_ = graph;
}

void Greedy::SetDijkstra(Dijkstra& dijkstra) {
  dijkstra_ = dijkstra;
}

Demand Greedy::GetDemand() {
  return demand_;
}

Graph Greedy::GetGraph() {
  return graph_;
}

void Greedy::DemandSort(std::vector<Request>& vecrequest) {
  for (int i = 0; i < vecrequest.size(); i++) {
    vecrequest[i].SetKey(rand() / static_cast<float>(Uniform(0, 1)));
  }
  sort(vecrequest.begin(), vecrequest.end(), comparision_request_by_key());
}

void Greedy::DemandSwap(std::vector<Request>& vecrequest) {
  vecrequest.push_back(vecrequest[0]);
  vecrequest.erase(vecrequest.begin());

  dijkstra_.paths_.push_back(dijkstra_.paths_[0]);
  dijkstra_.paths_.erase(dijkstra_.paths_.begin());
}

float Greedy::Execute(Graph& graph,
                      std::vector<Request>& vecrequest,
                      int qtvertex,
                      bool regenerateDijkstra) {
  if (regenerateDijkstra) {
    // Dijkstra dijkstra(vecrequest.size());
    dijkstra_.paths_.clear();
    dijkstra_.paths_.resize(vecrequest.size());
    // ObjDijkstra = dijkstra;
  }

  for (int p = 0; p < vecrequest.size(); p++) {
    dijkstra_.SetAllGraphEdgeIncCost(graph, qtvertex, vecrequest[p].GetQt());
    dijkstra_.GetCostByDijkstra(graph.GetAdjList(),
                                  qtvertex,
                                  vecrequest[p].GetSrc(),
                                  vecrequest[p].GetDst(),
                                  p);
    AddPath(graph, p, qtvertex, vecrequest[p].GetQt());
    // cout << "AQUI: " << p << endl;
  }

  // refine(graph, vecrequest, qtvertex);
  /* for(int p = 0; p < qtvertex; p++)
  {
      for(int x = 1; x < graph.getAdjList()[p].size(); x++)
      {
          totalcost += graph.getAdjList()[p][x].getCost();
      }
  } */

  // MinCost = totalcost;
  // graph.printWithQtRequests();
  return graph.GetTotalCost();;
}

float Greedy::DeletePath(Graph& graph, int path, int qtvertex, int qtrequests) {
  /* cout << "DIJKSTRA PATH FOR ADD: ";
  for(int v=0; v<ObjDijkstra.Paths[path].size(); v++)
  {
      cout << ObjDijkstra.Paths[path][v] << " - ";
  }
  cout << endl; */

  // cout << "DELETED PATH: \n";

  std::vector<int> path_cp = dijkstra_.paths_[path];
  for (int i = 0; i < path_cp.size() - 1; i++) {
    int z = path_cp[i], zprox = path_cp[i + 1], x = 1;
    while (x < graph.GetNeighbors(z).size()) {
      if (graph.GetNeighbors(z)[x].GetNumber() == zprox) {
        graph.GetNeighbors(z)[x].SetQtRequests
                      (graph.GetNeighbors(z)[x].GetQtRequests() - qtrequests);
        int w = graph.GetNeighbors(z)[x].GetQtRequests();
        float l = graph.GetNeighbors(z)[x].GetWeight();
        graph.GetNeighbors(z)[x].SetCost(functions_.Fwdm(w, l));
        // cout << "Deleting: " << graph.getNeighbors(z)[x].getNumber()
        //     << " - Path_CP: Z: " << z << " - Path_CP: ZPROX: "
        //     << zprox << " - Qt:" << qtrequests << endl;
        break;
      }
      x++;
    }
  }

  for (int i = path_cp.size() - 1; i >= 0; i--) {
    int z = path_cp[i], zprev = path_cp[i - 1],
        x = graph.GetNeighbors(z).size() - 1;
    while (x >= 1) {
      if (graph.GetNeighbors(z)[x].GetNumber() == zprev) {
        graph.GetNeighbors(z)[x].SetQtRequests
                       (graph.GetNeighbors(z)[x].GetQtRequests() - qtrequests);
        int w = graph.GetNeighbors(z)[x].GetQtRequests();
        float l = graph.GetNeighbors(z)[x].GetWeight();
        graph.GetNeighbors(z)[x].SetCost(functions_.Fwdm(w, l));
        // cout << "Deleting: " << graph.getNeighbors(z)[x].getNumber()
        //       << " - Path_CP: Z: " << z << " - Path_CP: ZPROX: "
        //       << zprox << " - Qt:" << qtrequests << endl;
        break;
      }
      x--;
    }
  }

  /* cout << endl << endl;
  graph.printWithQtRequests();
  graph.printWithCost();
  cout << "TOTAL COST: " << graph.getTotalCost();
  system("PAUSE");*/
  /* float totalcost = 0;
  for(int p = 0; p < qtvertex; p++)
  {
      for(int x = 1; x < graph.getAdjList()[p].size(); x++)
      {
          // cout << "TOTALCOST: " << graph.getAdjList()[p][x].getCost() << endl;
          totalcost += graph.getAdjList()[p][x].getCost();
      }
  }

  // return totalcost; */

  /* if(totalcost < 0) {
    cout << "Negative Actual Cost found: \n";
    graph.printWithQtRequests();
    cout << "DIJKSTRA PATH FOR ADD: \n";
    for(int v=0; v<ObjDijkstra.Paths[path].size(); v++) {
      cout << ObjDijkstra.Paths[path][v] << " - ";
    }
    cout << endl;
    system("PAUSE");
  } */
  return graph.GetTotalCost();;
}


float Greedy::AddPath(Graph& graph, int path, int qtvertex, int qtrequests) {
  /* cout << "DIJKSTRA PATH FOR ADD: ";
  for(int v=0; v<ObjDijkstra.Paths[path].size(); v++)
  {
      cout << ObjDijkstra.Paths[path][v] << " - ";
  }
  cout << endl; */

  // cout << "DELETED PATH: \n";

  std::vector<int> path_cp = dijkstra_.paths_[path];
  for (int i = 0; i < path_cp.size() - 1; i++) {
    int z = path_cp[i], zprox = path_cp[i + 1], x = 1;
    while (x < graph.GetNeighbors(z).size()) {
      if (graph.GetNeighbors(z)[x].GetNumber() == zprox) {
        graph.GetNeighbors(z)[x].SetQtRequests
                      (graph.GetNeighbors(z)[x].GetQtRequests() + qtrequests);
        int w = graph.GetNeighbors(z)[x].GetQtRequests();
        float l = graph.GetNeighbors(z)[x].GetWeight();
        graph.GetNeighbors(z)[x].SetCost(functions_.Fwdm(w, l));
        // cout << "Deleting: " << graph.getNeighbors(z)[x].getNumber()
        //     << " - Path_CP: Z: " << z << " - Path_CP: ZPROX: "
        //     << zprox << " - Qt:" << qtrequests << endl;
        break;
      }
      x++;
    }
  }

  for (int i = path_cp.size() - 1; i >= 0; i--) {
    int z = path_cp[i], zprev = path_cp[i - 1],
        x = graph.GetNeighbors(z).size() - 1;
    while (x >= 1) {
      if (graph.GetNeighbors(z)[x].GetNumber() == zprev) {
        graph.GetNeighbors(z)[x]
             .SetQtRequests
                     (graph.GetNeighbors(z)[x].GetQtRequests() + qtrequests);
        int w = graph.GetNeighbors(z)[x].GetQtRequests();
        float l = graph.GetNeighbors(z)[x].GetWeight();
        graph.GetNeighbors(z)[x].SetCost(functions_.Fwdm(w, l));
        // cout << "Deleting: " << graph.getNeighbors(z)[x].getNumber()
        //     << " - Path_CP: Z: " << z << " - Path_CP: ZPROX: "
        //     << zprox << " - Qt:" << qtrequests << endl;
        break;
      }
      x--;
    }
  }

  /* cout << endl << endl;
  graph.printWithQtRequests();
  graph.printWithCost();
  cout << "TOTAL COST: " << graph.getTotalCost();
  system("PAUSE");*/
  /* float totalcost = 0;
  for(int p = 0; p < qtvertex; p++)
  {
      for(int x = 1; x < graph.getAdjList()[p].size(); x++)
      {
          // cout << "TOTALCOST: " << graph.getAdjList()[p][x].getCost() << endl;
          totalcost += graph.getAdjList()[p][x].getCost();
      }
  }

  //return totalcost; */


  /* if(totalcost < 0) {
    cout << "Negative Actual Cost found: \n";
    graph.printWithQtRequests();
    cout << "DIJKSTRA PATH FOR ADD: \n";
    for(int v=0; v<ObjDijkstra.Paths[path].size(); v++) {
      cout << ObjDijkstra.Paths[path][v] << " - ";
    }
    cout << endl;
    system("PAUSE");
  } */
  return graph.GetTotalCost();
}


float Greedy::ExecuteWithRefine(Graph& graph,
                                std::vector<Request>& vecrequest) {
  float act = 0;
  graph.CleanCosts();
  act = Execute(graph, vecrequest, graph.GetQtVertex(), true);
  min_cost_ = act;

  int actrequest = -1, pathch = 1, mincostch = 0, lastalt = -2, loops = 0;
  std::vector<int> actpath;

  while (((pathch > 0) || (mincostch > 0)
          || (loops < 1)) && (lastalt != actrequest)) {
    if ((lastalt == actrequest) && (loops > 0)) {
      break;
    }

    if (actrequest == vecrequest.size() -1) {
      actrequest = -1;
      loops++;
    }

    actrequest++;

    pathch = 0;
    mincostch = 0;

    for (int i = 0; i < vecrequest.size(); i++) {
      actpath.clear();
      actpath = dijkstra_.paths_[i];

      DeletePath(graph, i, graph.GetQtVertex(), vecrequest[i].GetQt());
      dijkstra_.SetAllGraphEdgeIncCost
                 (graph, graph.GetQtVertex(), vecrequest[i].GetQt());
      dijkstra_.GetCostByDijkstra
                 (graph.GetAdjList(),
                  graph.GetQtVertex(),
                  vecrequest[i].GetSrc(),
                  vecrequest[i].GetDst(),
                  i);
      act = AddPath(graph, i, graph.GetQtVertex(), vecrequest[i].GetQt());

      if (act < min_cost_) {
        min_cost_ = act;
        mincostch++;
        lastalt = i;
        continue;
      }

      int u = 0;
      if (pathch == 0) {
        while (u < actpath.size()) {
          if (actpath[u] != dijkstra_.paths_[i][u]) {
            pathch++;
            lastalt = i;
            break;
          }
          u++;
        }
      }
    }
  }
  return min_cost_;
}


float Greedy::ExecuteWithRefine(Graph graph,
                                std::vector<Request> vecrequest,
                                std::vector<int> permutation) {
  std::vector<Request> aux;
  aux.resize(vecrequest.size());

  for (int i = 0; i < permutation.size(); i++) {
    aux.push_back(vecrequest[permutation[i]]);
  }

  float act = 0;
  graph.CleanCosts();
  act = Execute(graph, aux, graph.GetQtVertex(), true);

  min_cost_ = act;

  int actrequest = -1, pathch = 1, mincostch = 0, lastalt = -2, loops = 0;
  std::vector<int> actpath;

  // com actrequest = 0 ao ser declarado forco a primeira execucao do loop while
  // while(((path_ch > 0) || (min_cost_ch > 0)) || (actrequest < aux.size())) {
  while (((pathch > 0) || (mincostch > 0)
          || (loops < 1)) && (lastalt != actrequest)) {
    // act = deletePath(graph, 0, graph.getQtVertex(), aux[0].getQt());

    // DemandSwap(aux);
    if ((lastalt == actrequest) && (loops > 0)) {
      break;
    }

    if (actrequest == aux.size() -1) {
      actrequest = -1;
      loops++;
    }

    actrequest++;

    pathch = 0;
    mincostch = 0;

    for (int i = 0; i < aux.size(); i++) {
      actpath.clear();
      actpath = dijkstra_.paths_[i];
      /* if(i < aux.size() - 1)
      { */

      DeletePath(graph, i, graph.GetQtVertex(), aux[i].GetQt());
      dijkstra_.SetAllGraphEdgeIncCost
                 (graph, graph.GetQtVertex(), aux[i].GetQt());
      dijkstra_.GetCostByDijkstra
                 (graph.GetAdjList(),
                  graph.GetQtVertex(),
                  aux[i].GetSrc(),
                  aux[i].GetDst(),
                  i);
      act = AddPath(graph, i, graph.GetQtVertex(), aux[i].GetQt());

      if (act < min_cost_) {
        min_cost_ = act;
        mincostch++;
        lastalt = i;
        continue;
      }
      /* }
      else
      {
          ObjDijkstra.setAllGraphEdgeIncCost(graph, graph.getQtVertex(), aux[i].getQt());
          ObjDijkstra.getCostByDijkstra(graph.getAdjList(), graph.getQtVertex(), aux[i].getSrc(), aux[i].getDst(), i);
          act = addPath(graph, i, graph.getQtVertex(), aux[i].getQt());
      } */

      int u = 0;
      if (pathch == 0) {
        while (u < actpath.size()) {
          if (actpath[u] != dijkstra_.paths_[i][u]) {
            pathch++;
            lastalt = i;
            break;
          }
          u++;
        }
      }
    }
  }
  return min_cost_;
}
