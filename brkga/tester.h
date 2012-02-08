// Copyright 2011 Universidade Federal de Minas Gerais
// Autor: Luiz Gustavo Sathler Dias
// Projeto Orientado em Computa��o 2
// Defini��o de Classe Tester.

#ifndef PIFRO_TESTER_H_
#define PIFRO_TESTER_H_

#include <vector>
#include "./instance.h"

enum {GREEDY, PSC, GENETICA, GREEDY_T, PSC_T};

class Tester {
    public:
        // Construtor padr�o.
        Tester();
        // Destrutor padr�o.
        ~Tester();
        // Initializa Tester.
        void Initialize(Instance* instance);
        // Executa uma das heur�sticas correspondentes.
        void Execute(int type);
        // Imprime custo da melhor solu��o.
        void Print(double cost);
    private:
        std::vector<Request> unchanged_;
        char* output_name_;
        // Invoca execu��o da heur�stica Greedy.
        void ExecuteGreedy();
        // Invoca execu��o da heur�stica Psc.
        void ExecutePsc();
        // Invoca execu��o do algoritmo gen�tico.
        void ExecuteGeneticAlgorithm();
        // Gera Permuta��o de Requisi��es.
        void GeneratePermutation(std::vector<Request>& request);
        // Invoca execu��o da heur�stica Greedy tradicional
        // Usa apenas 20 permuta��es.
        void ExecuteGreedyT();
        // Invoca execu��o da heur�stica Psc tradicional
        // Usa apenas 20 permuta��es.
        void ExecutePscT();
};

#endif  // PIFRO_TESTER_H_
