// Copyright 2011 Universidade Federal de Minas Gerais
// Autor: Luiz Gustavo Sathler Dias
// Projeto Orientado em computa��o 2
// Defini��o de classe Dijkstra.

#ifndef PIFRO_DIJKSTRA_H_
#define PIFRO_DIJKSTRA_H_

#include <stdio.h>
#include <list>
#include <vector>
#include "./graph.h"
#include "./macros.h"

class Dijkstra {
    public:
        // Construtor padr�o.
        Dijkstra();

        // Destrutor padr�o.
        ~Dijkstra();

        // Retorna o custo de utilizar a aresta (i, j).
        float EdgeCost(int i, int j);

        // Inializa par�metros do algoritmo de Dijkstra.
        void Initialize(Graph* g, int start_pass);

        // Executa o algoritmo de Dijkstra.
        void Execute(int source, int destination);

        // Salva o caminho do v�rtice raiz at� o v�rtice destino
        // na lista path.
        bool GetPath(int source, int destination, std::list<int>* path);

    private:
        // Apenas refer�ncia para grafo. Inicializa��o externa a classe.
        Graph* g_;
        // Indica o n�mero de itera��es da heur�stica PSC
        // at� que a fun��o de custo se torne igual a Greedy.
        int p_;
        // Vetor de dist�ncias calculadas durante execu��o.
        std::vector<float> distance_;
        // ascendent_[i] guarda o v�rtice ascendente de i.
        std::vector<int> ascendent_;

        DISALLOW_COPY_AND_ASSIGN(Dijkstra);
};

#endif  // PIFRO_DIJKSTRA_H
