// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#include "./PSC.h"

PSC::PSC() {
}

PSC::PSC(Graph graph, Demand demand) {
  graph_ = graph;
  demand_ = demand;
}

PSC::PSC(int qtRequests) {
  Dijkstra tmp(qtRequests);
  dijkstra_ = tmp;
}

void PSC::DemandSwap() {
  demand_.vec_request_.push_back(demand_.vec_request_[0]);
  demand_.vec_request_.erase(demand_.vec_request_.begin());
  dijkstra_.paths_.push_back(dijkstra_.paths_[0]);
  dijkstra_.paths_.erase(dijkstra_.paths_.begin());
}

int PSC::makespin(){
  int power = (rand() % INT_MAX);
  int iret = 0, rest = (power % demand_.qt_wavelength_);
//  cout << "REST = " << rest;
  while(rest > 0){
    rest = rest - demand_.vec_request_[iret].qt_;
    if((iret < demand_.vec_request_.size() - 1) && (rest > 0)){
      iret++;
    }
    //cout << " - QTTMP = " << demand.vec_request_[iret].qt_;
  }

//  cout << " - POWER = " << power << " - WAVELENGTHS = " << demand_.qt_wavelength_ << " - REST = " << rest << " - IRET = " << iret << " - QT = " << demand_.vec_request_[iret].qt_ << endl;

/*  if((iret == demand_.vec_request_[iret].size()) || (rest > 0)){
    system("PAUSE");
  }*/

  return iret;
}

float PSC::Execute(bool regenerateDijkstra, bool demandSort) {
  if (demandSort) {
    demand_.Sort();
  }

  graph_.CleanCosts();

  if (regenerateDijkstra) {
    dijkstra_.paths_.clear();
    dijkstra_.paths_.resize(demand_.qt_request_);

    for (int p = 0; p < demand_.vec_request_.size(); p++) {
      AddPath(p, demand_.vec_request_[p].qt_, true, 0);
    }
  } else {
    for (int p = 0; p < demand_.vec_request_.size(); p++) {
      AddPath(p, demand_.vec_request_[p].qt_, false, 0);
    }
  }

  min_cost_ = graph_.GetTotalCost();

  return min_cost_;
}

float PSC::Execute(bool regenerateDijkstra, bool demandSort, time_t tstart, int tex) {
  if (demandSort) {
    demand_.Sort();
  }

  graph_.CleanCosts();

  if (regenerateDijkstra) {

    dijkstra_.paths_.clear();
    dijkstra_.paths_.resize(demand_.qt_request_);

    for (int p = 0; p < demand_.vec_request_.size(); p++) {
      if((time(NULL) - tstart) < tex){
        AddPath(p, demand_.vec_request_[p].qt_, true, 0 );
      }else{
        break;
      }
    }
  } else {
    for (int p = 0; p < demand_.vec_request_.size(); p++) {
      if((time(NULL) - tstart) < tex){
        AddPath(p, demand_.vec_request_[p].qt_, false, 0);
      }else{
        break;
      }
    }
  }

  if((time(NULL) - tstart) < tex){
    min_cost_ = graph_.GetTotalCost();
  }else{
    min_cost_ = FLT_MAX;
  }

  // graph_.PrintWithQtRequests();

  return min_cost_;
}

float PSC::DeletePath(int path, int qtrequests, int p) {
  std::vector<int> path_cp = dijkstra_.paths_[path];

  for (int i = 0; i < path_cp.size() - 1; i++) {
    int z = path_cp[i], zprox = path_cp[i + 1], x = 1;
    while (x < graph_.adj_list_[z].size()) {
      if (graph_.adj_list_[z][x].number_ == zprox) {
        graph_.adj_list_[z][x].qt_requests_ =
          (graph_.adj_list_[z][x].qt_requests_ - qtrequests);
        int w = graph_.adj_list_[z][x].qt_requests_;
        float l = graph_.adj_list_[z][x].weight_;
        graph_.adj_list_[z][x].cost_ = functions_.F_line_wdm(w, l, p);
        break;
      }
      x++;
    }
  }

  for (int i = path_cp.size() - 1; i > 0; i--) {
    int z = path_cp[i], zprev = path_cp[i - 1],
                                x = graph_.adj_list_[z].size() - 1;
    while (x >= 1) {
      if (graph_.adj_list_[z][x].number_ == zprev) {
        graph_.adj_list_[z][x].qt_requests_ =
          (graph_.adj_list_[z][x].qt_requests_ - qtrequests);
        int w = graph_.adj_list_[z][x].qt_requests_;
        float l = graph_.adj_list_[z][x].weight_;
        graph_.adj_list_[z][x].cost_ = functions_.F_line_wdm(w, l, p);
        break;
      }
      x--;
    }
  }

  min_cost_ = graph_.GetTotalCost();

  return  min_cost_;
}


float PSC::AddPath(int path, int qtrequests, bool search_new_path, int p) {
  if (search_new_path) {
    dijkstra_.paths_[path].clear();
    graph_ = dijkstra_.SetAllGraphEdgeIncCost(graph_, qtrequests, p);
    graph_ = dijkstra_.GetPathByDijkstra(graph_,
                                         demand_.vec_request_[path].src_,
                                         demand_.vec_request_[path].dst_,
                                         path,
                                         qtrequests);
  }

  std::vector<int> path_cp = dijkstra_.paths_[path];

  for (int i = 0; i < path_cp.size() - 1; i++) {
    int z = path_cp[i], zprox = path_cp[i + 1], x = 1;
    while (x < graph_.adj_list_[z].size()) {
      if (graph_.adj_list_[z][x].number_ == zprox) {
        graph_.adj_list_[z][x].qt_requests_ =
          (graph_.adj_list_[z][x].qt_requests_ + qtrequests);
        int w = graph_.adj_list_[z][x].qt_requests_;
        float l = graph_.adj_list_[z][x].weight_;
        graph_.adj_list_[z][x].cost_ = functions_.F_line_wdm(w, l, p);

              // Verificando se não ultrapassou a quantidade
              // de comprimentos de onda permitidos
              /*if(graph_.adj_list_[z][x].qt_requests_ > (ROADMLimit * U)){
              cout << "wavelengths limit reaching on fiber " <<
                 z << " - " << x << " - Wavelenghts amount: " <<
                 graph_.adj_list_[z][x].qt_requests_ << endl;
                 graph_.impossible_ = -1;
              //system("PAUSE");
            }*/

        break;
      }
      x++;
    }
  }

  for (int i = path_cp.size() - 1; i > 0; i--) {
    int z = path_cp[i], zprev = path_cp[i - 1],
                                x = graph_.adj_list_[z].size() - 1;
    while (x >= 1) {
      if (graph_.adj_list_[z][x].number_ == zprev) {
        graph_.adj_list_[z][x]
        .qt_requests_ =
          (graph_.adj_list_[z][x].qt_requests_ + qtrequests);
        int w = graph_.adj_list_[z][x].qt_requests_;
        float l = graph_.adj_list_[z][x].weight_;
        graph_.adj_list_[z][x].cost_ = functions_.F_line_wdm(w, l, p);
        break;
      }
      x--;
    }
  }

  min_cost_ = graph_.GetTotalCost();

  return min_cost_;
}


float PSC::ExecuteWithRefine(bool regenerate_dijkstra, bool demand_sort) {
  if (regenerate_dijkstra || demand_sort) {
    min_cost_ = Execute(regenerate_dijkstra, demand_sort);
  } else {
    min_cost_ = graph_.GetTotalCost();
  }

  int actrequest = -1, pathch = 1, mincostch = 0, lastalt = -2, loops = 0, p = 0;
  std::vector<int> actpath;

  while (((pathch > 0) || (mincostch > 0)
          || (loops < 1)) && (lastalt != actrequest)) {
    if ((lastalt == actrequest) && (loops > 0)) {
      break;
    }

    if (actrequest == demand_.vec_request_.size() -1) {
      actrequest = -1;
      loops++;
    }

    actrequest++;

    pathch = 0;
    mincostch = 0;

    for (int i = 0; i < demand_.vec_request_.size(); i++) {
      actpath.clear();
      actpath = dijkstra_.paths_[i];

      DeletePath(i, demand_.vec_request_[i].qt_, p);
      AddPath(i, demand_.vec_request_[i].qt_, true, p);

      if (graph_.GetTotalCost() != min_cost_) {
        mincostch++;
        if (min_cost_ > graph_.GetTotalCost()) {
          min_cost_ = graph_.GetTotalCost();
          lastalt = i;
        }
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

    if(p < P){
      p++;
    }
  }
  min_cost_ = graph_.GetTotalCost();

  return min_cost_;
}

float PSC::ExecuteWithRefine(bool regenerate_dijkstra, bool demand_sort, time_t tstart, int tex) {
  if (regenerate_dijkstra || demand_sort) {
    min_cost_ = Execute(regenerate_dijkstra, demand_sort, tstart, tex);
  } else {
    min_cost_ = graph_.GetTotalCost();
  }

  int actrequest = -1, pathch = 1, mincostch = 0, lastalt = -2, loops = 0, p = 0;
  std::vector<int> actpath;

  while (((pathch > 0) || (mincostch > 0)
          || (loops < 1)) && (lastalt != actrequest) && ((time(NULL) - tstart) < tex)) {
    if ((lastalt == actrequest) && (loops > 0)) {
      break;
    }

    if (actrequest == demand_.vec_request_.size() -1) {
      actrequest = -1;
      loops++;
    }

    actrequest++;

    pathch = 0;
    mincostch = 0;

    for (int i = 0; i < demand_.vec_request_.size(); i++) {
      if((time(NULL) - tstart) < tex){
      actpath.clear();
      actpath = dijkstra_.paths_[i];

      DeletePath(i, demand_.vec_request_[i].qt_, p);
      AddPath(i, demand_.vec_request_[i].qt_, true, p);

      if (graph_.GetTotalCost() != min_cost_) {
        mincostch++;
        if (min_cost_ > graph_.GetTotalCost()) {
          min_cost_ = graph_.GetTotalCost();
          lastalt = i;
        }
      }
      //cout << "PSC MIN COST: " << min_cost_ << "\n";

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
    }else{
      break;
    }
    }

    if(p < P){
      p++;
    }
  }
  if((time(NULL) - tstart) < tex){
    min_cost_ = graph_.GetTotalCost();
  }else{
    min_cost_ = FLT_MAX;
  }
  return min_cost_;
}

float PSC::ExecuteWithRefine(std::vector<int> permutation, time_t tstart, int tex) {
  std::vector<Request> aux;

  for (int i = 0; i < permutation.size(); i++) {
    aux.push_back(demand_.vec_request_[permutation[i]]);
  }

  demand_.vec_request_ = aux;
  //min_cost_ = Execute(true, false);
  if((time(NULL) - tstart) < tex){
    min_cost_ = ExecuteWithRefine(true, false, tstart, tex);
  }else{
    min_cost_ = FLT_MAX;
  }
  return min_cost_;
}


float PSC::ExecuteWithRefine(int k, bool roulete) {
  std::vector<Request> rnd_requests;
  int x = 0;

  while (x < k) {

    int r = 0;
    if(roulete){
        r = makespin();
    }else{
       r = (rand() % demand_.vec_request_.size());
    }

    DeletePath(r, demand_.vec_request_[r].qt_, 0);
    dijkstra_.paths_.push_back(dijkstra_.paths_[r]);
    dijkstra_.paths_.erase(dijkstra_.paths_.begin() + r);
    rnd_requests.push_back(demand_.vec_request_[r]);
    demand_.vec_request_.erase(demand_.vec_request_.begin() + r);
    x++;
  }

  for (x = 0; x < rnd_requests.size(); x++) {
    demand_.vec_request_.push_back(rnd_requests[x]);
  }

  for (x = demand_.vec_request_.size() - k;
       x < demand_.vec_request_.size(); x++) {
    AddPath(x, demand_.vec_request_[x].qt_, true, 0);
  }

  //min_cost_ = ExecuteWithRefine(false, false);
  min_cost_ = graph_.GetTotalCost();

  return min_cost_;
}

float PSC::ExecuteWithRefine(int k, time_t tstart, int tex, bool roulete){
  std::vector<Request> rnd_requests;
  int x = 0;

  while ((x < k) && ((time(NULL) - tstart) < tex)) {

    int r = 0;
    if(roulete == true){
        r = makespin();
    }else{
       r = (rand() % demand_.vec_request_.size());
    }

    DeletePath(r, demand_.vec_request_[r].qt_, 0);
    dijkstra_.paths_.push_back(dijkstra_.paths_[r]);
    dijkstra_.paths_.erase(dijkstra_.paths_.begin() + r);
    rnd_requests.push_back(demand_.vec_request_[r]);
    demand_.vec_request_.erase(demand_.vec_request_.begin() + r);
    x++;
  }

  for (x = 0; x < rnd_requests.size(); x++) {
    if((time(NULL) - tstart) < tex){
      demand_.vec_request_.push_back(rnd_requests[x]);
    }else{
      break;
    }
  }

  for (x = demand_.vec_request_.size() - k;
       x < demand_.vec_request_.size(); x++) {
         if((time(NULL) - tstart) < tex){
           AddPath(x, demand_.vec_request_[x].qt_, true, 0);
         }else{
           break;
         }
  }

  //min_cost_ = ExecuteWithRefine(false, false);
  if((time(NULL) - tstart) < tex){
    min_cost_ = graph_.GetTotalCost();
  }else{
    min_cost_ = FLT_MAX;
  }

  return min_cost_;
}
