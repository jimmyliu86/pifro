/*
    Copyright 2011 Luiz Gustavo Sathler Dias
    Projeto Orientado em Computacao 2
	Implementacao da estrutura Grafo
*/

#include "./graph.h"

#include <stdio.h>

Graph::Graph(int n) {
    this->number_of_vertex_ = n;

    matrix_ = new int*[n];
    list_ = new std::list<int>[n];

    for (int i = 0; i < n; ++i) {
        matrix_[i] = new int[n];
        for (int j = 0; j < n; ++j)
            matrix_[i][j] = -1;
    }
}

Graph::~Graph() {
    for (int i = 0; i < number_of_vertex_; ++i)
        delete[] matrix_[i];
    delete[] matrix_;
    delete[] list_;
}

void Graph::AddEdge(int i, int j) {
    matrix_[i][j] = 0;
    list_[i].push_back(j);
}

void Graph::DeleteEdge(int i, int j) {
    matrix_[i][j] = -1;
    list_[i].remove(j);
}

int Graph::GetCost(int i, int j) const {
    return matrix_[i][j];
}

int Graph::Size() const {
    return number_of_vertex_;
}

const std::list<int>& Graph::GetNeighbors(int i) const {
    return list_[i];
}
