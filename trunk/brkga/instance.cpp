/*
    Copyright 2011 Luiz Gustavo Sathler Dias
    Projeto Orientado em Computacao 2
    Classe de implementacao de instancia
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "./instance.h"

Instance* Instance::instance_ = NULL;

Instance::Instance() {
}

Instance::~Instance() {
    delete g_;
    delete[] instance_name_;
}

void Instance::Initialize(const char* instance_filename) {
    instance_name_ = strdup(instance_filename);

    char connections_filename[30];
    char requests_filename[30];
    /* adicionar extensao .net e .trf ao nome da instancia.
    Arquivo de conexoes e arquivo de requisicoes de trafego */
    sprintf(connections_filename, "%s.net", instance_filename);
    sprintf(requests_filename, "%s.trf", instance_filename);
    // le dados da instancia
    instance_->ReadConnectionsFile(connections_filename);
    instance_->ReadRequestsFile(requests_filename);
}

Instance* Instance::GetInstance() {
    if (instance_ == NULL) {
        printf("Instance not initialized\n");
        exit(1);
    }
    return instance_;
}

void Instance::Print() {
    printf("Instance name: %s\n", instance_name_);
    printf("Nodes: %d\n", number_of_node_);
    printf("Edges: %d\n", number_of_edge_);
    printf("Requests: %d\n\n", number_of_request_);
    printf("Topology:\n");
    g_->Print();
    printf("Requests:\n");
    std::vector<std::pair<int, int> >::iterator it;
    for (it = request_.begin(); it != request_.end(); ++it)
        printf("%d %d\n", it->first, it->second);
}

int Instance:: GetNumberOfRequest() const {
    return number_of_request_;
}

// Le arquivo com as conexoes existententes na rede
void Instance::ReadConnectionsFile(const char* connections_filename) {
    FILE* connections_file = fopen(connections_filename, "r");
    if (connections_file == NULL) {
        printf("file %s not found\n", connections_filename);
        exit(0);
    }

    // le numero de nos e numero de conexoes
    fscanf(connections_file, "%d %d", &number_of_node_,
           &number_of_edge_);

    // initializa grafo
    g_ = new Graph(number_of_node_);
    int n1, n2;
    // adiciona conexoes no grafo que representa a topologia da rede
    for (int i = 0; i < number_of_edge_; ++i) {
        fscanf(connections_file, "%d %d", &n1, &n2);
        g_->AddEdge(n1, n2);
    }
    fclose(connections_file);
}

// Le arquivo com as requisicoes de trafego
void Instance::ReadRequestsFile(const char* requests_filename) {
    FILE* requests_file = fopen(requests_filename, "r");
    if (requests_file == NULL) {
        printf("file %s not found\n", requests_filename);
        exit(1);
    }

    // le numero de requisicoes
    fscanf(requests_file, "%d", &number_of_request_);
    int r1, r2;
    // le par de requisicoes de trafego
    for (int i = 0; i < number_of_request_; ++i) {
        fscanf(requests_file, "%d %d", &r1, &r2);
        request_.push_back(std::pair<int, int>(r1, r2));
    }
    fclose(requests_file);
}
