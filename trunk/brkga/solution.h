// Copyright 2011 Universidade Federal de Minas Gerais
// Projeto Orientado em Computação 2
// Classe de definição da solução do problema.

#ifndef PIFRO_SOLUTION_H_
#define PIFRO_SOLUTION_H_

#include <list>
#include "./graph.h"

class Solution {
    public:
        // Contrutor inicializa lista de rotas.
        Solution(int number_of_request, Graph* g);

        // Destrutor padrão.
        ~Solution();

        // Imprime as rotas e o custo da solução.
        void PrintToFile();

        // Retorna o custo da solução.
        float GetCost(int pass);

        // Adiciona a rota da conexão id_path à solução e
        // atualiza os fluxos nos enlaces da rede.
        void AddPath(int id_path, const std::list<int>& tpath);

        // Remove uma rota da solução e atualiza
        // o fluxo nos enlaces da rede.
        void DeletePath(int id_path);

    private:
        // Custo da solução.
        float cost_;
        int number_of_request_;
        // Guarda as rotas das conexões. Ownership: Solution.
        std::list<int>* path_;
        // Inicializado na clase Instance.
        Graph* g_;

        // Retorna o custo do enlace (i, j)
        // Dependendo do passo do algoritmo a função
        // de custos pode alterar-se.
        float EdgeCost(int pass, int i, int j) const;
};

#endif  // PIFRO_SOLUTION_H_
