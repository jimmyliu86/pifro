#ifndef BRKGA_H
#define BRKGA_H

#include <float.h>
#include <stdio.h>
//#include <resource.h>
//#include <sys/time.h>

#include <algorithm>
#include <list>

#include <time.h>

#include "../Greedy.h"
#include "../Graph.h"
#include "../Request.h"

typedef struct Chromosome
{
    std::vector<Request> gen;
    double cost;
} Chromosome;

class BRKGA
{
public:
    BRKGA(int population_size,
                     int size_of_setA,
                     int size_of_setB,
                     int size_of_setC,
                     float prob_crossover,
                     std::vector<Request>& vecrequest,
                     Graph& graph);
    ~BRKGA();
    void InitializePopulation();
    void SortRequest();
    void SortPopulation();
    void UpdateCrossoverPopulation();
    void Crossover();
    void Crossover2();
    void GenerateMutation();
    void SaveBestIndividual();
    void CalculateFitness();
    void PrintToFile(float time);
    float ExecuteWithGreedy(int timeexec);

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
    Graph objGraph;
    time_t TStart;
    int TimeExec;
};

#endif // BRKGA_H
