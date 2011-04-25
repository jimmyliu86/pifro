/*
    Copyright 2011 Luiz Gustavo Sathler Dias
    Projeto Orientado em Computacao 2
	Implementacao da estrutura Grafo
*/

#include "grafo.h"
#include <stdio.h>

Graph::Graph(int nVertex) {
    this->nVertex_ = nVertex;

    adjacencyMatrix_ = new int*[nVertex];
    for (int i = 0; i < nVertex; ++i) {
        adjacencyMatrix_[i] = new int[nVertex];
        for (int j = 0; j < nVertex; ++j)
            adjacencyMatrix_[i][j] = -1;
    }
}

Graph::Graph(const Graph& g) {
    this->nVertex_ = g.nVertex_;

    this->adjacencyMatrix_ = new int*[g.nVertex_];
    for (int i = 0; i < g.nVertex_; ++i) {
        this->adjacencyMatrix_[i] = new int[g.nVertex_];
        for (int j = 0; j < g.nVertex_; ++j)
            this->adjacencyMatrix_[i][j] = g.adjacencyMatrix_[i][j];
    }
}

void Graph::AddEdge(int i, int j) {
    adjacencyMatrix_[i][j] = 0;
}

void Graph::DeleteEdge(int i, int j) {
    adjacencyMatrix_[i][j] = -1;
}

int Graph::GetCost() const {
	return adjacencyMatrix_[i][j];
}

void Graph::Print() {
    for (int i = 0; i < nVertex_; ++i) {
        for (int j = 0; j <nVertex_; ++j) {
            printf("%d ", adjacencyMatrix_[i][j]);
        }
        printf("\n");
    }
}

Graph::~Graph() {
    for (int i = 0; i < nVertex_; ++i)
        delete[] adjacencyMatrix_[i];

    delete[] adjacencyMatrix_;
}

