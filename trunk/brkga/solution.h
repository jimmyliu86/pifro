// Copyright 2011 Universidade Federal de Minas Gerais
// Projeto Orientado em Computa��o 2
// Classe de defini��o da solu��o do problema.

#ifndef PIFRO_SOLUTION_H_
#define PIFRO_SOLUTION_H_

#include <list>
#include "./graph.h"

class Solution {
    public:
        // Contrutor inicializa lista de rotas.
        Solution(int number_of_request, Graph* g);

        // Destrutor padr�o.
        ~Solution();

        // Imprime as rotas e o custo da solu��o.
        void PrintToFile();

        // Retorna o custo da solu��o.
        float GetCost(int pass);

        // Adiciona a rota da conex�o id_path � solu��o e
        // atualiza os fluxos nos enlaces da rede.
        void AddPath(int id_path, const std::list<int>& tpath);

        // Remove uma rota da solu��o e atualiza
        // o fluxo nos enlaces da rede.
        void DeletePath(int id_path);

    private:
        // Custo da solu��o.
        float cost_;
        int number_of_request_;
        // Guarda as rotas das conex�es. Ownership: Solution.
        std::list<int>* path_;
        // Inicializado na clase Instance.
        Graph* g_;

        // Retorna o custo do enlace (i, j)
        // Dependendo do passo do algoritmo a fun��o
        // de custos pode alterar-se.
        float EdgeCost(int pass, int i, int j) const;
};

#endif  // PIFRO_SOLUTION_H_
