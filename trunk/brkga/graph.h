/*
    Copyright 2011 Luiz Gustavo Sathler Dias
    Projeto Orientado em Computacao 2
    Classe de definicao de Grafo.
    Representa o grafo como matriz e lista
    de adjacencia.
*/

#ifndef BRKGA_GRAPH_H_
#define BRKGA_GRAPH_H_

#include <list>

class Graph {
    public:
        /* Construtor recebe numero de vertices
           e aloca memoria para matriz e lista
           de adjacencias */
        explicit Graph(int n);

        ~Graph();

        // Insere uma aresta no grafo
        void AddEdge(int i, int j);

        // Exclui uma aresta do grafo
        void DeleteEdge(int i, int j);

        // Retorna o peso de uma aresta
        int GetCost(int i, int j) const;

        // Incrementa peso de uma aresta
        void SetCost(int i, int j, int cost);

        // Retorna o numero de vertices do grafo
        int Size() const;

        // Retorna uma lista com os vizinhos do vertice i
        const std::list<int> &GetNeighbors(int i) const;

        // Imprime grafo
        void Print();

    private:
        int **matrix_;
        std::list<int> *list_;
        int number_of_vertex_;
};

#endif  // BRKGA_GRAPH_H_
