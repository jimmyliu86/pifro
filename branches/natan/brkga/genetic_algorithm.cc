// Copyright 2011 Universidade Federal de Minas Gerais
// Autor: Luiz Gustavo Sathler Dias
// Projeto Orientado em Computação 2
// Implementação da classe algoritmo genético.

#include "./genetic_algorithm.h"

#include <float.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>

#include <algorithm>
#include <list>

#include "./heuristic.h"

bool compare_hop(const Request& i, const Request& j) {
    return i.hop > j.hop;
}

GeneticAlgorithm::GeneticAlgorithm(int population_size,
                                     int size_of_setA,
                                     int size_of_setB,
                                     int size_of_setC,
                                     float prob_crossover,
                                     std::vector<Request>& request) {
    population_size_ = population_size;
    size_setA_ = size_of_setA;
    size_setB_ = size_of_setB;
    size_setC_ = size_of_setC;
    original_ = request;
    prob_crossover_ = prob_crossover;

    // Pre-ordena requisições por caminho mais curto.
    std::sort(original_.begin(), original_.end(), compare_hop);
}

void GeneticAlgorithm::InitializePopulation() {
    // Inicializa população inicial gerada
    // de forma aleatória.
    population_.reserve(population_size_);
    for (int i = 0; i < population_size_; ++i) {
        Chromosome individual;
        Request g;
        for (int j = 0; j < original_.size(); ++j) {
            g.src = original_[j].src;
            g.dst = original_[j].dst;
            g.id = original_[j].id;
            g.key = rand() / static_cast<float>(RAND_MAX);
            g.hop = original_[j].hop;
            individual.gen.push_back(g);
        }
		population_.push_back(individual);
    }
    // Inicializa lista de individuos temporários
    // Usada na operação de crossover.
    cross_pop_.resize(size_setB_);
    for (int i = 0; i < size_setB_; ++i) {
        cross_pop_[i].gen.resize(original_.size());
    }

    // Inicializa melhor individuo.
    best_individual_.gen.resize(original_.size());
    best_individual_.cost = DBL_MAX;
}

GeneticAlgorithm::~GeneticAlgorithm() {
}
// Função de custo alterada para (i.key + i.hop). Ordenação decrescente.
bool compare_key(const Request& i, const Request& j) {
    return (i.key+i.hop) > (j.key+j.hop);
}

bool compare_cost(const Chromosome& i, const Chromosome& j) {
    return i.cost < j.cost;
}

void GeneticAlgorithm::SortRequest() {
    for (int i = 0; i < population_size_; ++i) {
        std::sort(population_[i].gen.begin(), population_[i].gen.end(),
                  compare_key);
    }
}

void GeneticAlgorithm::SortPopulation() {
    std::sort(population_.begin(), population_.end(), compare_cost);
}


void GeneticAlgorithm::UpdateCrossoverPopulation() {
    int k = size_setA_;
    for (int i = 0; i < size_setB_; ++i) {
        for (int j = 0; j < original_.size(); ++j)
            population_[k].gen[j] = cross_pop_[i].gen[j];
        std::sort(population_[k].gen.begin(), population_[k].gen.end(), compare_key);
        ++k;
    }
}

// Crossover baseado em biased key genetic algorithm.
void GeneticAlgorithm::Crossover() {
    int current = 0;
    for (int i = 0; i < size_setB_; ++i) {
        int elite = rand() % size_setA_;
        int non_elite = (rand() % size_setB_) + size_setA_;
        float crossover;
        for (int j = 0; j < original_.size(); ++j) {
            crossover = rand() / static_cast<float>(RAND_MAX);
            if(crossover < prob_crossover_) {
                cross_pop_[current].gen[j].key = population_[elite].gen[j].key;
            }
            else {
                cross_pop_[current].gen[j].key = population_[non_elite].gen[j].key;
            }
            cross_pop_[current].gen[j].src = original_[j].src;
            cross_pop_[current].gen[j].dst = original_[j].dst;
        }
        ++current;
    }
    UpdateCrossoverPopulation();
}

// Crossover baseado em algoritmo genético tradicional.
void GeneticAlgorithm::Crossover2() {
    std::vector<int> mask;
    std::list<int> unfilled;
    mask.resize(original_.size());
    int current = 0;
    for (int i = 0; i < size_setB_; ++i) {
        int elite = rand() % size_setA_;
        int non_elite = (rand() % size_setB_) + size_setA_;
        float crossover;
        for (int j = 0; j < original_.size(); ++j) {
            crossover = rand() / static_cast<float>(RAND_MAX);
            if(crossover < prob_crossover_) {
                mask[population_[elite].gen[j].id]  = 1;
                cross_pop_[current].gen[j] = population_[elite].gen[j];
            }
            else {
                mask[population_[elite].gen[j].id] = 0;
                unfilled.push_back(j);
            }
        }
        // Preenche restande do cromossomo com valores
        // de indivíduo não-elite.
            int j = 0, unfilled_position;
            while(!unfilled.empty() && j < original_.size()) {
                int index_non_elite = population_[non_elite].gen[j].id;
                if (mask[index_non_elite] == 0) {
                    unfilled_position = unfilled.front();
                    unfilled.pop_front();
                    cross_pop_[current].gen[unfilled_position] =
                    population_[non_elite].gen[j];
                }
                ++j;
            }
        ++current;
    }
    UpdateCrossoverPopulation();
}

void GeneticAlgorithm::GenerateMutation() {
    int start = population_.size() - size_setC_;
    for (int i = 0; i < size_setC_; ++i) {
        for (int j = 0; j < original_.size(); ++j) {
            population_[start].gen[j] = original_[j];
            population_[start].gen[j].key = rand() / static_cast<float>(RAND_MAX);
        }
        population_[start].cost = 0.0f;
        ++start;
    }
    start = population_.size() - size_setC_;
    for (int i = start; i < population_.size(); ++i)
        std::sort(population_[i].gen.begin(),population_[i].gen.end(),
                  compare_key);
}

void GeneticAlgorithm::SaveBestIndividual() {
    double cost_elite = population_[0].cost;
    if (cost_elite < best_individual_.cost) {
        best_individual_.cost = cost_elite;
        for (int i = 0; i < original_.size(); ++i)
            best_individual_.gen[i] = population_[0].gen[i];

        struct rusage times;
        getrusage(0, &times);
        float telapsed = times.ru_utime.tv_sec + times.ru_utime.tv_usec*0.000001;
        printf("GA - custo: %lf, tempo: %lf\n", cost_elite, telapsed);
    }
}

void GeneticAlgorithm::CalculateFitness() {
    double cost;
    Heuristic psc;
    for (int i = 0; i < population_.size(); ++i) {
        cost = psc.Execute(population_[i].gen, 0, 100);
        population_[i].cost = cost;
    }
}

void GeneticAlgorithm::PrintToFile(float time) {
    //printf("%f\n", time);
    printf("%.0lf\n", best_individual_.cost);
}

double GeneticAlgorithm::Execute() {
    struct rusage times;
    float telapsed;

    InitializePopulation();
    SortRequest();
    CalculateFitness();
    SortPopulation();
    SaveBestIndividual();

    while(1) {
        Crossover();
        GenerateMutation();
        CalculateFitness();
        SortPopulation();
        SaveBestIndividual();

        getrusage(0, &times);
        telapsed = times.ru_utime.tv_sec +
    times.ru_utime.tv_usec*0.000001;
       // printf("%.4lf\n",ttranscorrido);
        if(telapsed > 3*600.0f) {
            break;
        }
    }
    //PrintToFile(telapsed);
    return best_individual_.cost;
}
