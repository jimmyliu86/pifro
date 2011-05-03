/* 
    Copyright 2011 Luiz Gustavo Sathler Dias
    Projeto Orientado em Computacao 2
    Classe de definicao da Instancia
*/

#ifndef BRKGA_INSTANCE_H_
#define BRKGA_INSTANCE_H_

#include <vector>
#include <utility>
#include "./graph.h"
#include "./macros.h"

class Instance {
    public:

        ~Instance();

        void Initialize(const char* instance_filename);

        // Retorna ponteiro para instancia inicializada
        static Instance* GetInstance();

        // Imprime os dados da instancia
        void Print();

        int GetNumberOfRequest() const;

    private:

        const char* instance_name_;
        int number_of_node_;
        int number_of_edge_;
        int number_of_request_;
        Graph* g_;
        std::vector<std::pair<int, int> > request_;

        // Classe singleton
        static Instance* instance_;

        // Construtor padrao
        Instance();

        // Faz leitura dos arquivos com as conexoes e requisicoes
        // de trafego
        void ReadConnectionsFile(const char* connection_file_name);
        void ReadRequestsFile(const char* request_file_name);

        DISALLOW_COPY_AND_ASSIGN(Instance);
};

#endif  // BRKGA_INSTANCE_H_
