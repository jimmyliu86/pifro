// Copyright 2011 Universidade Federal de Minas Gerais
// Projeto Orientado em computação 2
// Implementação do algoritmo de Dijkstra.

#include "./dijkstra.h"
#include <float.h>
#include <math.h>
#include "./constants.h"
#include "./heap.h"

Dijkstra::Dijkstra() {
}

Dijkstra::~Dijkstra() {
}

// Retorna o custo passar mais uma conexao pela aresta (i, j)
// Se p_ < kConvergence a função de custo utilizada é de PSC, caso contrário
// função de custo Greedy.
inline float Dijkstra::EdgeCost(int i, int j) {
    if (p_ < kConvergence) {
        float ratio1 = static_cast<float>(g_->GetCost(i, j) + 1) /
                       kRoadmCapacity;
        float fx1 = floor(ratio1) + sqrt((ratio1) - floor(ratio1));
        float total1 = (static_cast<float> (p_) / kConvergence) * ceil(ratio1) +
                   (static_cast<float>(kConvergence - p_) / kConvergence) * fx1;
        total1 *= kRoadmCost;
        float ratio2 = static_cast<float>(g_->GetCost(i, j)) /
                       kRoadmCapacity;
        float fx2 = floor(ratio2) + sqrt((ratio2) - floor(ratio2));
        float total2 = (static_cast<float>(p_) / kConvergence) * ceil(ratio2) +
                  (static_cast<float>(kConvergence - p_) / kConvergence) * fx2;
        total2 *= kRoadmCost;
        float total = total1 - total2;
        return total;
    } else {
        float ratio1 = ceil(static_cast<float>(g_->GetCost(i, j) + 1) /
                       kRoadmCapacity);
        float total1 = ratio1 * kRoadmCost;
        float ratio2 = ceil(static_cast<float>(g_->GetCost(i, j)) /
                       kRoadmCapacity);
        float total2 = ratio2 * kRoadmCost;
        float total = total1 - total2;
        return total;
    }
}

void Dijkstra::Initialize(Graph* g, int start_pass) {
    g_ = g;
    p_ = start_pass;
}

// Executa o algoritmo de Dijkstra a partir do vértice source.
void Dijkstra::Execute(int source, int destination) {
    distance_.resize(g_->Size());
    ascendent_.resize(g_->Size());
    // Inicializa distancia como infinito
    // e ascendente como indefinido.
    for (int i = 0; i < distance_.size(); ++i) {
        distance_[i] = FLT_MAX;
        ascendent_[i] = -1;
    }
    // Distância da raiz igual a 0.
    distance_[source] = 0.0f;

    HeapMin Q(distance_, distance_.size());
    Q.MakeHeap();
    // Enquanto fila não estiver vazia.
    while (!Q.Empty()) {
        int vertex = Q.ExtractMin();
        
        if (vertex == destination) return;
 
        std::list<int> neighbors = g_->GetNeighbors(vertex);
        std::list<int>::iterator it;
        for (it = neighbors.begin(); it != neighbors.end();
             ++it) {
            float cost = distance_[vertex] + EdgeCost(vertex, *it);
            // Verifica se existe um caminho mais barato para it.
            if (distance_[*it] > cost) {
                Q.DecreaseKey(*it, cost);
                ascendent_[*it] = vertex;
            }
        }
    }
}

// Reconstroi o caminho da raiz até o destino
// Retorna verdadeiro caso o caminho seja recontruido corretamente.
bool Dijkstra::GetPath(int source, int destination,
                         std::list<int>* path) {
    if (distance_[destination] < FLT_MAX) {
        int current = destination;
        path->push_front(current);
        current = ascendent_[destination];
        while (current != source) {
            path->push_front(current);
            current = ascendent_[current];
        }
        path->push_front(current);
        return true;
    }
    return false;
}
