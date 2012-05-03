// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#include <algorithm>
#include <vector>

#include "./greedy.h"

Greedy::Greedy(Graph graph, Demand demand) {
  graph_ = graph;
  demand_ = demand;
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

void Greedy::DemandSort() {
  srand(time(NULL));
  for (int i = 0; i < demand_.GetVecRequest().size(); i++) {
    // vecrequest[i].SetKey((static_cast<float>(Uniform(0, 1)) / rand()));
    demand_.GetVecRequest()[i].SetKey(myrand);
    // cout << "RANDOM " << vecrequest[i].GetKey()<<endl;
  }
  sort(demand_.GetVecRequest().begin(), demand_.GetVecRequest().end(), comparision_request_by_key());
}

void Greedy::DemandSwap() {
  demand_.GetVecRequest().push_back(demand_.GetVecRequest()[0]);
  demand_.GetVecRequest().erase(demand_.GetVecRequest().begin());

  dijkstra_.paths_.push_back(dijkstra_.paths_[0]);
  dijkstra_.paths_.erase(dijkstra_.paths_.begin());
}

float Greedy::Execute(bool regenerateDijkstra) {

  // ALEATORIOS
  DemandSort();

  if (regenerateDijkstra) {
    // Dijkstra dijkstra(vecrequest.size());
    dijkstra_.paths_.clear();
    dijkstra_.paths_.resize(demand_.GetVecRequest().size());
    // ObjDijkstra = dijkstra;
  }

  for (int p = 0; p < demand_.GetVecRequest().size(); p++) {
    dijkstra_.SetAllGraphEdgeIncCost(graph_, demand_.GetVecRequest()[p].GetQt());
    dijkstra_.GetCostByDijkstra(graph_,
                                demand_.GetVecRequest()[p].GetSrc(),
                                demand_.GetVecRequest()[p].GetDst(),
                                p);
    AddPath(p, demand_.GetVecRequest()[p].GetQt());
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
  // graph_.PrintWithIncCost();
  float cost = graph_.GetTotalCost();
  // cout << "EXECUTE COST: " << cost << endl;
  return cost;
}

float Greedy::DeletePath(int path, int qtrequests) {
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
    while (x < graph_.GetNeighbors(z).size()) {
      if (graph_.GetNeighbors(z)[x].GetNumber() == zprox) {
        graph_.GetNeighbors(z)[x].SetQtRequests
                      (graph_.GetNeighbors(z)[x].GetQtRequests() - qtrequests);
        int w = graph_.GetNeighbors(z)[x].GetQtRequests();
        float l = graph_.GetNeighbors(z)[x].GetWeight();
        graph_.GetNeighbors(z)[x].SetCost(functions_.Fwdm(w, l));
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
        x = graph_.GetNeighbors(z).size() - 1;
    while (x >= 1) {
      if (graph_.GetNeighbors(z)[x].GetNumber() == zprev) {
        graph_.GetNeighbors(z)[x].SetQtRequests
                       (graph_.GetNeighbors(z)[x].GetQtRequests() - qtrequests);
        int w = graph_.GetNeighbors(z)[x].GetQtRequests();
        float l = graph_.GetNeighbors(z)[x].GetWeight();
        graph_.GetNeighbors(z)[x].SetCost(functions_.Fwdm(w, l));
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
  return graph_.GetTotalCost();;
}


float Greedy::AddPath(int path, int qtrequests) {
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
    while (x < graph_.GetNeighbors(z).size()) {
      if (graph_.GetNeighbors(z)[x].GetNumber() == zprox) {
        graph_.GetNeighbors(z)[x].SetQtRequests
                      (graph_.GetNeighbors(z)[x].GetQtRequests() + qtrequests);
        int w = graph_.GetNeighbors(z)[x].GetQtRequests();
        float l = graph_.GetNeighbors(z)[x].GetWeight();
        graph_.GetNeighbors(z)[x].SetCost(functions_.Fwdm(w, l));
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
        x = graph_.GetNeighbors(z).size() - 1;
    while (x >= 1) {
      if (graph_.GetNeighbors(z)[x].GetNumber() == zprev) {
        graph_.GetNeighbors(z)[x]
             .SetQtRequests
                     (graph_.GetNeighbors(z)[x].GetQtRequests() + qtrequests);
        int w = graph_.GetNeighbors(z)[x].GetQtRequests();
        float l = graph_.GetNeighbors(z)[x].GetWeight();
        graph_.GetNeighbors(z)[x].SetCost(functions_.Fwdm(w, l));
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
  return graph_.GetTotalCost();
}


float Greedy::ExecuteWithRefine() {
  float act = 0;
  graph_.CleanCosts();
  act = Execute(true);
  //dijkstra_.PrintPaths();
  min_cost_ = act;

  int actrequest = -1, pathch = 1, mincostch = 0, lastalt = -2, loops = 0;
  std::vector<int> actpath;

  while (((pathch > 0) || (mincostch > 0)
          || (loops < 1)) && (lastalt != actrequest)) {
    if ((lastalt == actrequest) && (loops > 0)) {
      break;
    }

    if (actrequest == demand_.GetVecRequest().size() -1) {
      actrequest = -1;
      loops++;
    }

    actrequest++;

    pathch = 0;
    mincostch = 0;

    for (int i = 0; i < demand_.GetVecRequest().size(); i++) {
      actpath.clear();
      actpath = dijkstra_.paths_[i];

      DeletePath(i, demand_.GetVecRequest()[i].GetQt());
      dijkstra_.SetAllGraphEdgeIncCost
                 (graph_, demand_.GetVecRequest()[i].GetQt());
      dijkstra_.GetCostByDijkstra
                 (graph_,
                  demand_.GetVecRequest()[i].GetSrc(),
                  demand_.GetVecRequest()[i].GetDst(),
                  i);
      act = AddPath(i, demand_.GetVecRequest()[i].GetQt());

      if (act < min_cost_) {
        min_cost_ = act;
        mincostch++;
        lastalt = i;
        //continue;
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
  // cout << "GRAPH COST: " << graph_.GetTotalCost() << endl;
  // cout << "EXECUTEWITHREFINE() COST: "  << min_cost_ << endl;
  return min_cost_;
}


float Greedy::ExecuteWithRefine(std::vector<int> permutation) {
  std::vector<Request> aux;
  aux.resize(demand_.GetVecRequest().size());

  //std::vector<std::vector<int> > aux_paths;

  //cout << "PERMUTATION SIZE: " << permutation.size() <<  endl;
  //cout << "VECREQUEST SIZE: " << demand_.GetVecRequest().size() <<  endl;
  for (int i = 0; i < permutation.size(); i++) {
    aux.push_back(demand_.GetVecRequest()[permutation[i]]);
    //aux_paths.push_back(dijkstra_.paths_[permutation[i]]);
  }

  demand_.SetVecRequest(aux);
  //dijkstra_.paths_ = aux_paths;

  float act = 0;

  graph_.CleanCosts();
  act = Execute(true);

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

      DeletePath(i, aux[i].GetQt());
      graph_ = dijkstra_.SetAllGraphEdgeIncCost
                 (graph_, aux[i].GetQt());
      graph_ = dijkstra_.GetCostByDijkstra
                 (graph_,
                  aux[i].GetSrc(),
                  aux[i].GetDst(),
                  i);
      act = AddPath(i, aux[i].GetQt());

      if (act < min_cost_) {
        min_cost_ = act;
        mincostch++;
        lastalt = i;
        //continue;
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
  // cout << "EXECUTEWITHREFINE(PERMUTATION) COST: "  << min_cost_ << endl;
  return min_cost_;
}


float Greedy::ExecuteWithRefine(int k) {
  float act = 0;

  // Talvez devesse comentar as proximas 2 linhas
  graph_.CleanCosts();
  act = Execute(true);

  min_cost_ = act;

  int actrequest = -1, pathch = 1, mincostch = 0, lastalt = -2, loops = 0;
  std::vector<int> actpath;

  while (((pathch > 0) || (mincostch > 0)
          || (loops < 1)) && (lastalt != actrequest)) {
    if ((lastalt == actrequest) && (loops > 0)) {
      break;
    }

    if (actrequest == demand_.GetVecRequest().size() -1) {
      actrequest = -1;
      loops++;
    }

    actrequest++;

    pathch = 0;
    mincostch = 0;

    for (int i = k; i < demand_.GetVecRequest().size(); i++) {
      actpath.clear();
      actpath = dijkstra_.paths_[i];

      // Excluindo K rotas
      for(int x = 0; x < k; x++) {
        DeletePath(x, demand_.GetVecRequest()[x].GetQt());
      }

      graph_ = dijkstra_.SetAllGraphEdgeIncCost
                 (graph_, demand_.GetVecRequest()[i].GetQt());
      graph_ = dijkstra_.GetCostByDijkstra
                 (graph_,
                  demand_.GetVecRequest()[i].GetSrc(),
                  demand_.GetVecRequest()[i].GetDst(),
                  i);

      AddPath(i, demand_.GetVecRequest()[i].GetQt());

      //Adicionando novamente as k rotas removidas
      for(int x = 0; x < k; x++) {
        act = AddPath(i, demand_.GetVecRequest()[i].GetQt());
      }


      if (act < min_cost_) {
        min_cost_ = act;
        mincostch++;
        lastalt = i;
        //continue;
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
