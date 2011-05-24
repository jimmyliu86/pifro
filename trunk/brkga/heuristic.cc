// Copyright 2011 Universidade Federal de Minas Gerais
// Projeto Orientado em Computação 2
// Classe de definição das heurísticas Greedy e PSC.

#include "./heuristic.h"

#include <float.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

#include "./constants.h"
#include "./dijkstra.h"

Heuristic::Heuristic() {
    instance_ = Instance::GetInstance();
    s_ = new Solution(instance_->GetNumberOfRequest(), instance_->GetGraph());
}

Heuristic::~Heuristic() {

}

// Função temporária. Mover para solução. 
void Heuristic::PrintToFile(float cost) {
    char fout_name[40];
    sprintf(fout_name, "%s.out", instance_->GetName());
    FILE *fout = fopen(fout_name, "w");
    fprintf(fout, "%.0f\n", cost);
}



float Heuristic::Execute(const std::vector<Request>& getRequest,
                        int startup,
                        int iteration) {
    Dijkstra d;
    float cost, min_cost = FLT_MAX;
    std::list<int> path;
    Request r;
    std::vector<Request> request = getRequest;

    for (int i = startup; i < startup + iteration; ++i) {
        // Processa cada uma das requisições.
        for (int j = 0; j < request.size(); ++j) {
            r = request[j];
            s_->DeletePath(j);
            path.clear();
            d.Initialize(instance_->GetGraph(), i);
            d.Execute(r.src, r.dst);
            if (d.GetPath(r.src, r.dst, &path) == false) {
                printf("path not found\n");
            }
            s_->AddPath(j, path);
        } 
        // Calcula o custo da solução atual.
        if (i >= kConvergence) {
            cost = s_->CalculateCost(i);
            // Guarda menor custo da solução.
            if (cost < min_cost)
                min_cost = cost;
            else // Se o custo não melhorou em relação a iteração anterior.
                break;
        } else {
            cost = s_->CalculateCost(i);
          }
    }
    for (int j = 0; j < request.size(); ++j)
        s_->DeletePath(j);

    //PrintToFile(min_cost);
    return min_cost;
}


