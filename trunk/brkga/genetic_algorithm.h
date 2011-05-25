// Copyright 2011 Universidade Federal de Minas Gerais
// Projeto Orientado em Computa��o 2]
// Defini��o da classe Algoritmo gen�tico.

#ifndef BRKGA_GENETICA_H_
#define BRKGA_GENETICA_H_

#include <vector>

#include "./instance.h"

typedef struct Chromosome {
    std::vector<Request> gen;
    float cost;
}Chromosome;

class GeneticAlgorithm {
    public:
        GeneticAlgorithm(int population_size,
                         int size_of_setA,
                         int size_of_setB,
                         int size_of_setC,
                         float prob_crossover,
                         std::vector<Request>& request);
        ~GeneticAlgorithm();
        void InitializePopulation();
        void SortRequest();
        void SortPopulation();
        void UpdateCrossoverPopulation();
        void Crossover();
        void GenerateMutation();
        void SaveBestIndividual();
        void CalculateFitness();
        void PrintToFile(float time);
        void Execute();
    private:
        std::vector<Chromosome> population_;
        std::vector<Chromosome> cross_pop_;
        Chromosome best_individual_;
        int size_setA_;
        int size_setB_;
        int size_setC_;
        int population_size_;
        float prob_crossover_;
        std::vector<Request> original_;
};

#endif  // BRKGA_GENETICA_H_