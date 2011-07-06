// Copyright 2011 Universidade Federal de Minas Gerais
// Projeto Orientado em Computação 2
// Implementação da Classe Tester.

#include "./tester.h"

#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>

#include <algorithm>

#include "./heuristic.h"
#include "./genetic_algorithm.h"

Tester::Tester() {
}

Tester::~Tester() {
}

void Tester::Initialize(Instance *instance) {
    char tmp_name[50];
    sprintf(tmp_name, "%s.out", instance->GetName());
    output_name_ = strdup(tmp_name);
    // Copia vetor de requisições de instância.
    std::vector<Request> tmp = instance->GetRequest();
    std::vector<Request>::iterator it;
    unchanged_.reserve(instance->GetNumberOfRequest());
    for (it = tmp.begin(); it!= tmp.end(); ++it)
        unchanged_.push_back(*it);
    
    //for (int i = 0; i < unchanged_.size(); ++i) {
    //    printf("%d %d %d\n", unchanged_[i].src,
    //                         unchanged_[i].dst,
    //                         unchanged_[i].hop);
    //}
}


struct my_comparison {
    public:
        bool operator()(const Request& a, const Request& b) const {
            return a.key < b.key;
        }
};

void Tester::GeneratePermutation(std::vector<Request>& request) {
    request.clear();
    request.reserve(unchanged_.size());
    for (int i = 0; i < unchanged_.size(); ++i) {
        request.push_back(unchanged_[i]);
        request[i].key = rand() / static_cast<float>(RAND_MAX);
    }
    std::sort(request.begin(), request.end(), my_comparison());
}

void Tester::Execute(int type) {
    switch(type) {
        case GREEDY:
            ExecuteGreedy();
            break;
        case PSC:
            ExecutePsc();
            break;
        case GENETICA:
            ExecuteGeneticAlgorithm();
            break;
        case GREEDY_T:
            ExecuteGreedyT();
            break;
        case PSC_T:
            ExecutePscT();
            break;
        default:
            printf("invalid option\n");
            exit(1);
    }
}

void Tester::Print(float cost) {
    FILE* output = fopen(output_name_, "ab");
    if (output == NULL) {
        printf("cant open file\n");
        exit(1);
    }
    fprintf(output, "%.0f\n", cost);
}

void Tester::ExecuteGreedy() {
    struct rusage times;
    float telapsed;
    std::vector<Request> request;
    Heuristic greedy;
    float cost, min_cost = FLT_MAX;
    
    while (true) {
        GeneratePermutation(request);
        cost = greedy.Execute(request, 5, 100);
        if (cost < min_cost)
            min_cost = cost;
        
        getrusage(0, &times);
        telapsed = times.ru_utime.tv_sec +
        times.ru_utime.tv_usec*0.000001;
        // printf("%.4lf\n",telapsed); 10 minutos.
        if(telapsed > 600.0f) {
            break;
        }
    }
    Print(min_cost);
}

void Tester::ExecutePsc() {
    struct rusage times;
    float telapsed;
    std::vector<Request> request;
    Heuristic psc;    
    float cost, min_cost = FLT_MAX;

    while (true) {
        GeneratePermutation(request);
        cost = psc.Execute(request, 0, 100);
        if (cost < min_cost)
            min_cost = cost;
        
        getrusage(0, &times);
        telapsed = times.ru_utime.tv_sec +
        times.ru_utime.tv_usec*0.000001;
        // printf("%.4lf\n",telapsed); 10 minutos.
        if(telapsed > 600.0f) {
            break;
        }
		//printf("%.0f\n", min_cost);
    }
    Print(min_cost);
}

void Tester::ExecuteGeneticAlgorithm() {
    GeneticAlgorithm ga(100, 20, 70, 10, 0.70f, unchanged_);
    float min_cost = ga.Execute();
    Print(min_cost);
}

void Tester::ExecuteGreedyT() {
    std::vector<Request> request;
    Heuristic greedy;
    float cost, min_cost = FLT_MAX;
    int iteration = 20; 
    while (iteration-- > 0) {
        GeneratePermutation(request);
        cost = greedy.Execute(request, 5, 100);
        if (cost < min_cost)
            min_cost = cost;
    }
    Print(min_cost);
}

void Tester::ExecutePscT() {
    std::vector<Request> request;
    Heuristic psc;    
    float cost, min_cost = FLT_MAX;
    int iteration = 20;

    while (iteration-- > 0) {
        GeneratePermutation(request);
        cost = psc.Execute(request, 0, 100);
        if (cost < min_cost)
            min_cost = cost;
    }
    Print(min_cost);
}
