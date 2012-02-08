// Copyright 2011 Universidade Federal de Minas Gerais
// Autor: Luiz Gustavo Sathler Dias
// Projeto Orientado em Computação 2
// Definição de Classe Tester.

#ifndef PIFRO_TESTER_H_
#define PIFRO_TESTER_H_

#include <vector>
#include "./instance.h"

enum {GREEDY, PSC, GENETICA, GREEDY_T, PSC_T};

class Tester {
    public:
        // Construtor padrão.
        Tester();
        // Destrutor padrão.
        ~Tester();
        // Initializa Tester.
        void Initialize(Instance* instance);
        // Executa uma das heurísticas correspondentes.
        void Execute(int type);
        // Imprime custo da melhor solução.
        void Print(double cost);
    private:
        std::vector<Request> unchanged_;
        char* output_name_;
        // Invoca execução da heurística Greedy.
        void ExecuteGreedy();
        // Invoca execução da heurística Psc.
        void ExecutePsc();
        // Invoca execução do algoritmo genético.
        void ExecuteGeneticAlgorithm();
        // Gera Permutação de Requisições.
        void GeneratePermutation(std::vector<Request>& request);
        // Invoca execução da heurística Greedy tradicional
        // Usa apenas 20 permutações.
        void ExecuteGreedyT();
        // Invoca execução da heurística Psc tradicional
        // Usa apenas 20 permutações.
        void ExecutePscT();
};

#endif  // PIFRO_TESTER_H_
