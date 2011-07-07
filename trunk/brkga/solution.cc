// Copyright 2011 Universidade Federal de Minas Gerais
// Autor: Luiz Gustavo Sathler Dias
// Projeto Orientado em Computação 2
// Classe de implementação da solução do problema.

#include "./solution.h"
#include <math.h>
#include <stdio.h>
#include "./constants.h"


Solution::Solution(int number_of_request, Graph* g) {
    number_of_request_ = number_of_request;
    path_ = new std::list<int>[number_of_request];
    g_ = g;
}

Solution::~Solution() {
    delete[] path_;
}

double Solution::GetCost() const {
    return cost_;
}

double Solution::CalculateCost(int pass) {
    cost_ = 0.0f;
    for (int i = 0; i < g_->Size(); ++i) {
        for (int j = 0; j < g_->Size(); ++j) {
            if (g_->IsEdge(i, j))
                cost_ += EdgeCost(pass, i, j);
        }
    }
    return cost_;
}

void Solution::AddPath(int id_path, const std::list<int>& tpath) {
    std::list<int>::const_iterator it1, it2;
    int size = tpath.size();
    it1 = tpath.begin();
    // Adiciona rota de uma conexao à solução.
    while (size-- > 1) {
        it2 = it1;
        ++it2;
        path_[id_path].push_back(*it1);
        // Atualiza fluxo no enlace da rede.
        g_->IncrementCost(*it1, *it2);
        ++it1;
    }
    path_[id_path].push_back(*it2);
}

void Solution::DeletePath(int id_path) {
    std::list<int>::iterator it1, it2;
    int size = path_[id_path].size(), cnt = 0;
    it1 = path_[id_path].begin();
    
    while (size-- > 1) {
        it2 = it1;
        ++it2;
        // Atualiza fluxo no enlace da rede.
        g_->DecrementCost(*it1, *it2);
        ++it1;
    }
    path_[id_path].clear();
}

// Retorna o custo do enlace (i, j)
// Se pass < kConvergence a função de custo utilizada é de PSC,
// caso contrário função de custo é Greedy.
float Solution::EdgeCost(int pass, int i, int j) const {
    float total, ratio;
    if (pass < kConvergence) {
        ratio = static_cast<float>(g_->GetCost(i, j)) /
                       kRoadmCapacity;
        float fx = floor(ratio) + sqrt((ratio) - floor(ratio));
        total = (static_cast<float>(pass) / kConvergence) * ceil(ratio) +
                (static_cast<float>(kConvergence - pass) / kConvergence) * fx;
        total *= kRoadmCost;
    } else {
        ratio = ceil(static_cast<float>(g_->GetCost(i, j)) /
                       kRoadmCapacity);
        total = ratio * kRoadmCost;
    }
    return total;
}

void Solution::PrintToFile() {
    for (int i = 0; i < number_of_request_; ++i) {
        std::list<int>::iterator it;
        for (it = path_[i].begin(); it != path_[i].end(); ++it) {
            printf("%d ", *it);
        }
        printf("\n");
    }
}
