// Copyright 2011 Universidade Federal de Minas Gerais
// Projeto Orientado em Computação 2
// Classe de definição de Grafo
// Representa o grafo como matriz e lista de adjacência.

#ifndef BRKGA_GRAPH_H_
#define BRKGA_GRAPH_H_

#include <list>

class Graph {
    public:
        // Recebe número de vértices e aloca
        // memória para matriz e lista
        // de adjacências.
        explicit Graph(int n);

        ~Graph();

        // Insere uma aresta no grafo.
        void AddEdge(int i, int j);

        // Exclui uma aresta do grafo.
        void DeleteEdge(int i, int j);

        // Retorna o peso de uma aresta.
        int GetCost(int i, int j) const;

        // Incrementa peso de uma aresta.
        void SetCost(int i, int j, int cost);

        // Incrementa 1 unidade de uma aresta.
        void IncrementCost(int i, int j);

        // Decrementa 1 unidade de uma aresta.
        void DecrementCost(int i, int j);

        // Checa se aresta (i,j) existe.
        bool IsEdge(int i, int j) const;

        // Retorna o numero de vértices do grafo.
        int Size() const;

        // Retorna uma lista com os vizinhos do vertice i.
        const std::list<int> &GetNeighbors(int i) const;

        // Imprime grafo.
        void Print();

    private:
        // Matriz inicializada nesta classe.
        int** matrix_;
        // Lista de Adjacência inicializada nesta classe.
        std::list<int>* list_;
        int number_of_vertex_;
};

#endif  // BRKGA_GRAPH_H_
