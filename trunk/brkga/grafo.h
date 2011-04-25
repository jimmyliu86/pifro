/*
    Copyright 2011 Luiz Gustavo Sathler Dias
   	Projeto Orientado em Computacao 2
	Classe de definicao de Grafo
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
		    int GetCost(int i, int j) const;
	private:
        int **adjacencyMatrix_;
        int nVertex_;
};

#endif
