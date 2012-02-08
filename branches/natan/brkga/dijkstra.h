// Copyright 2011 Universidade Federal de Minas Gerais
// Autor: Luiz Gustavo Sathler Dias
// Projeto Orientado em computação 2
// Definição de classe Dijkstra.

#ifndef PIFRO_DIJKSTRA_H_
#define PIFRO_DIJKSTRA_H_

#include <stdio.h>
#include <list>
#include <vector>
#include "./graph.h"
#include "./macros.h"

class Dijkstra {
    public:
        // Construtor padrão.
        Dijkstra();

        // Destrutor padrão.
        ~Dijkstra();

        // Retorna o custo de utilizar a aresta (i, j).
        float EdgeCost(int i, int j);

        // Inializa parâmetros do algoritmo de Dijkstra.
        void Initialize(Graph* g, int start_pass);

        // Executa o algoritmo de Dijkstra.
        void Execute(int source, int destination);

        // Salva o caminho do vértice raiz até o vértice destino
        // na lista path.
        bool GetPath(int source, int destination, std::list<int>* path);

    private:
        // Apenas referência para grafo. Inicialização externa a classe.
        Graph* g_;
        // Indica o número de iterações da heurística PSC
        // até que a função de custo se torne igual a Greedy.
        int p_;
        // Vetor de distâncias calculadas durante execução.
        std::vector<float> distance_;
        // ascendent_[i] guarda o vértice ascendente de i.
        std::vector<int> ascendent_;

        DISALLOW_COPY_AND_ASSIGN(Dijkstra);
};

#endif  // PIFRO_DIJKSTRA_H
