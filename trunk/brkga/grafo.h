/*
    Copyright 2010 Luiz Gustavo Sathler Dias
    Disciplina:  Heuristicas e Metaheuristicas
*/

#ifndef GRAPH_H_
#define GRAPH_H_

class Graph {
    public:
        explicit Graph(int nVertex);
        explicit Graph(const Graph& g);
         ~Graph();
        void AddEdge(int i, int j);
        void Print();
        void DeleteEdge(int i, int j);
        int **adjacencyMatrix_;
        int nVertex_;
};

#endif
