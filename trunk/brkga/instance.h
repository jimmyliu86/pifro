// Copyright 2011 Universidade Federal de Minas Gerais
// Projeto Orientado em Computação 2
// Classe de definição da instância do problema.

#ifndef BRKGA_INSTANCE_H_
#define BRKGA_INSTANCE_H_

#include <utility>
#include <vector>
#include "./graph.h"
#include "./macros.h"

class Instance {
    public:
        // Destrutor padrão.
        ~Instance();

        static void Initialize(const char* connections_filename,
                        const char* requests_filename);

        // Retorna ponteiro para instância inicializada.
        static Instance* GetInstance();

        // Imprime os dados da instância.
        void Print();
        
        // Retorna número de requisições.
        int GetNumberOfRequest() const;

        // Retorna Grafo com topologia da rede.
        Graph* GetGraph();

        // Retorna conjunto de requisições.
        const std::vector<std::pair<int, int> >& GetRequest() const;

    private:
        const char* instance_name_;
        int number_of_node_;
        int number_of_edge_;
        int number_of_request_;

        // Grafo inicializado nesta classe.
        Graph* g_;

        // Par de requisição (origem,destino).
        std::vector<std::pair<int, int> > request_;

        // Ponteiro para instância. Classe Instance permite
        // que apenas um objeto seja criado (singleton).
        // Inicializado em main.
        static Instance* instance_;

        // Construtor padrão.
        Instance();

        // Faz leitura dos arquivos com as conexões e requisições de tráfego.
        void ReadConnectionsFile(const char* connection_file_name);
        void ReadRequestsFile(const char* request_file_name);

        // Extrai nome da instância.
        void ExtractInstanceName(const char* filename);        

        DISALLOW_COPY_AND_ASSIGN(Instance);
};

#endif  // BRKGA_INSTANCE_H_
