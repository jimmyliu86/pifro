/* 
    Copyright 2011 Luiz Gustavo Sathler Dias
    Projeto Orientado em Computacao 2
    Classe de definicao da Instancia
*/

#ifndef INSTANCE_H_
#define INSTANCE_H_

#include <vector>
#include <utility>

#include "graph.h"

class Instance {
    public:

        ~Instance();
        void Initialize(const char* instance_filename);
        static Instance* instance();
        void Print();
   
    private:

        const char* instance_name_;
        int number_of_node_;
        int number_of_edge_;
        int number_of_request_;
        Graph* g_;
        std::vector<std::pair<int, int> > request_;
        
        static Instance* instance_;
        Instance();

        void ReadConnectionsFile(const char* connection_file_name);
        void ReadRequestsFile(const char* request_file_name);
};

#endif  // INSTANCE_H_
