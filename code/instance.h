// Copyright 2011 Universidade Federal de Minas Gerais
// Autor: Luiz Gustavo Sathler Dias
// Projeto Orientado em Computa��o 2
// Classe de defini��o da inst�ncia do problema.

#ifndef BRKGA_INSTANCE_H_
#define BRKGA_INSTANCE_H_

#include <utility>
#include <vector>
#include "./graph.h"
#include "./macros.h"

enum {NET_TYPE, TRF_TYPE};

class Instance {
    public:
        // Destrutor padr�o.
        ~Instance();

	static void Initialize(const char* net_file);
	
        static void Initialize(const char* net_file, const char* trf_file);

        // Retorna ponteiro para inst�ncia inicializada.
        static Instance* GetInstance();

        // Imprime os dados da inst�ncia.
        void Print();

        // Retorna Grafo com topologia da rede.
        Graph* GetGraph();

        // Retorna nome da inst�ncia.
        const char* GetName() const;

        // Grava grafo atual no arquivo
        void DumpNet(const char* file);

        void set_complete_graph(bool enable);
        bool complete_graph() const;

    private:
        char* instance_name_;
        int instance_type_;
        int number_of_node_;
        int number_of_edge_;
        bool complete_graph_;

        // Grafo inicializado nesta classe.
        Graph* g_;

        // Ponteiro para inst�ncia. Classe Instance permite
        // que apenas um objeto seja criado (singleton).
        // Inicializado em main.
        static Instance* instance_;

        // Construtor padr�o.
        Instance();

        // Faz leitura dos arquivos com as conex�es e requisi��es de tr�fego.
        void ReadConnectionsFile(const char* connection_file_name);

	// Faz leitura dos arquivos com as conex�es e requisi��es de tr�fego.
        void ReadConnectionsFile(const char* connection_file_name, const char* edge_file_name);
	
        // Extrai nome da inst�ncia.
        void ExtractInstanceName(const char* filename);        

        DISALLOW_COPY_AND_ASSIGN(Instance);
};

#endif  // BRKGA_INSTANCE_H_
