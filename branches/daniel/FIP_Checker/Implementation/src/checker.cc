// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#include "checker.h"

Checker::Checker()
{
  //ctor
}

Checker::~Checker()
{
  //dtor
}

float Checker::MergeGraphAndDemand(Graph& graph, Demand& demand) {
  for(int q = 0; q < demand.vec_request_.size(); q++) {
//    for (int i = 0; i < demand.vec_request_[q].size() - 1; i++) {
      int z = demand.vec_request_[q].src_, zprox = demand.vec_request_[q].dst_, x = 1;
      while (x < graph.adj_list_[z].size()) {
        if (graph.adj_list_[z][x].number_ == zprox) {
          graph.adj_list_[z][x].qt_requests_ =
            (graph.adj_list_[z][x].qt_requests_ + demand.vec_request_[q].qt_);
          int w = graph.adj_list_[z][x].qt_requests_;
          float l = graph.adj_list_[z][x].weight_;
          graph.adj_list_[z][x].cost_ = functions_.Fwdm(w, l);
          break;
        }
        x++;
      }
    }

    for (int i = demand.vec_request_.size() - 1; i > 0; i--) {
      int z = demand.vec_request_[i].dst_, zprev = demand.vec_request_[i].src_,
                                  x = graph.adj_list_[z].size() - 1;
      while (x >= 1) {
        if (graph.adj_list_[z][x].number_ == zprev) {
          graph.adj_list_[z][x]
          .qt_requests_ =
            (graph.adj_list_[z][x].qt_requests_ + demand.vec_request_[i].qt_);
          int w = graph.adj_list_[z][x].qt_requests_;
          float l = graph.adj_list_[z][x].weight_;
          graph.adj_list_[z][x].cost_ = functions_.Fwdm(w, l);
          break;
        }
        x--;
      }
    }

  return graph.GetTotalCost();
}
