// Copyright 2011 Universidade Federal de Minas Gerais
// Projeto Orientado em Computa��o 2
// Classe de defini��o das heur�sticas Greedy e PSC.

#ifndef PIFRO_HEURISTIC_H_
#define PIFRO_HEURISTIC_H_

#include "./instance.h"
#include "./solution.h"

class Heuristic {
    public:
        // Construtor padr�o.
        Heuristic();
        // Destrutor padr�o.
        ~Heuristic();
        // Executa uma das heur�sticas (Greedy ou PSC)
        // Depende do par�metro startup
        // iteration indica o n�mero m�ximo de itera��es.
        float Execute(const std::vector<Request>& getRequest,
                     int startup,
                     int iteration);
        
        void GetSolution(Solution *S);

        void PrintToFile(float cost);
    private:
        Solution *s_;
        Instance *instance_;
};

#endif  // PIFRO_HEURISTIC_H_
