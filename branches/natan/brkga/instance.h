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

typedef struct Request {
    int src;
    int dst;
    int id;
    float key;
    int hop;
}Request;

enum {NET_TYPE, SND_TYPE};

class Instance {
    public:
        // Destrutor padr�o.
        ~Instance();

        static void Initialize(const char* connections_filename,
                        const char* requests_filename);

        // Retorna ponteiro para inst�ncia inicializada.
        static Instance* GetInstance();

        // Imprime os dados da inst�ncia.
        void Print();
        
        // Retorna n�mero de requisi��es.
        int GetNumberOfRequest() const;

        // Retorna Grafo com topologia da rede.
        Graph* GetGraph();

        // Retorna conjunto de requisi��es.
        const std::vector<Request>& GetRequest() const;

        // Retorna nome da inst�ncia.
        const char* GetName() const;

        // Calcula a dist�ncia (em saltos) de origem ao destino.
        void CalculateHops();
    private:
        const char* instance_name_;
        int instance_type_;
        int number_of_node_;
        int number_of_edge_;
        int number_of_request_;

        // Grafo inicializado nesta classe.
        Graph* g_;

        // Par de requisi��o (origem,destino).
        std::vector<Request> request_;

        // Ponteiro para inst�ncia. Classe Instance permite
        // que apenas um objeto seja criado (singleton).
        // Inicializado em main.
        static Instance* instance_;

        // Construtor padr�o.
        Instance();

        // Faz leitura dos arquivos com as conex�es e requisi��es de tr�fego.
        void ReadConnectionsFile(const char* connection_file_name);
        void ReadRequestsFile(const char* request_file_name);

        // Extrai nome da inst�ncia.
        void ExtractInstanceName(const char* filename);        

        // Realiza busca em profundidade a partir do n� fonte
        // de uma requisi��o.
        void BreadthFirst(Request& i);

        DISALLOW_COPY_AND_ASSIGN(Instance);
};

#endif  // BRKGA_INSTANCE_H_
