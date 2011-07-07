// Copyright 2011 Universidade Federal de Minas Gerais
// Autor: Luiz Gustavo Sathler Dias
// Projeto Orientado em Computação 2
// Classe de definição das heurísticas Greedy e PSC.

#ifndef PIFRO_HEURISTIC_H_
#define PIFRO_HEURISTIC_H_

#include "./instance.h"
#include "./solution.h"

class Heuristic {
    public:
        // Construtor padrão.
        Heuristic();
        // Destrutor padrão.
        ~Heuristic();
        // Executa uma das heurísticas (Greedy ou PSC)
        // Depende do parâmetro startup
        // iteration indica o número máximo de iterações.
        double Execute(const std::vector<Request>& getRequest,
                     int startup,
                     int iteration);
        
        void GetSolution(Solution *S);

        void PrintToFile(double cost);
    private:
        Solution *s_;
        Instance *instance_;
};

#endif  // PIFRO_HEURISTIC_H_
