// Copyright 2011 Universidade Federal de Minas Gerais
// Projeto Orientado em Computa��o 2
// Classe de defini��o das heur�sticas Greedy e PSC.

#include "./heuristic.h"

#include <float.h>

#include "./constants.h"
#include "./dijkstra.h"

Heuristic::Heuristic() {
    instance_ = Instance::GetInstance();
    s_ = new Solution(instance_->GetNumberOfRequest(), instance_->GetGraph());
}

Heuristic::~Heuristic() {

}

void Heuristic::Execute(int startup, int iteration) {
    Dijkstra d;
    float cost, min_cost = FLT_MAX;
    std::list<int> path;
    std::pair<int, int> r;
    std::vector<std::pair<int, int> > request = instance_->GetRequest();

    for (int i = startup; i < startup + iteration; ++i) {
        // Processa cada uma das requisi��es.
        for (int j = 0; j < request.size(); ++j) {
            r = request[j];
            s_->DeletePath(j);
            path.clear();
            d.Initialize(instance_->GetGraph(), i);
            d.Execute(r.first);
            if (d.GetPath(r.first, r.second, &path) == false) {
                printf("path not found\n");
            }
            s_->AddPath(j, path);
        } 
        // Calcula o custo da solu��o atual.
        if (i >= kConvergence) {
            cost = s_->CalculateCost(i);
            // Guarda menor custo da solu��o.
            if (cost < min_cost)
                min_cost = cost;
            else // Se o custo n�o melhorou em rela��o a itera��o anterior.
                break;
        } else {
            cost = s_->CalculateCost(i);
        }
    }
    printf("Min Cost\n");
    printf("%.0f\n", min_cost);
    //s_->PrintToFile();
    //printf("\n====\n\n");
    //Graph* t = instance_->GetGraph();
    //t->PrintMatrix();
}


