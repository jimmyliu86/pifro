// Copyright 2011 Universidade Federal de Minas Gerais
// Projeto Orientado em Computa��o 2
// Classe de implementa��o de inst�ncia.

#include "./instance.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    // Adiciona extens�o .net e .trf ao nome da inst�ncia.
    // Arquivo de conex�es e arquivo de requisi��es de tr�fego.
    sprintf(connections_filename, "%s.net", instance_filename);
    sprintf(requests_filename, "%s.trf", instance_filename);
    // L� dados da inst�ncia.
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

// L� arquivo com as conex�es existentes na rede.
void Instance::ReadConnectionsFile(const char* connections_filename) {
    FILE* connections_file = fopen(connections_filename, "r");
    if (connections_file == NULL) {
        printf("file %s not found\n", connections_filename);
        exit(1);
    }

    // L� n�mero de n�s e n�mero de conex�es
    fscanf(connections_file, "%d %d", &number_of_node_,
           &number_of_edge_);

    // Initializa grafo.
    g_ = new Graph(number_of_node_);
    int n1, n2;
    // Adiciona conex�es no grafo que representa a topologia da rede.
    for (int i = 0; i < number_of_edge_; ++i) {
        fscanf(connections_file, "%d %d", &n1, &n2);
        g_->AddEdge(n1, n2);
    }
    fclose(connections_file);
}

// L� arquivo com as requisic�es de tr�fego.
void Instance::ReadRequestsFile(const char* requests_filename) {
    FILE* requests_file = fopen(requests_filename, "r");
    if (requests_file == NULL) {
        printf("file %s not found\n", requests_filename);
        exit(1);
    }

    // L� n�mero de requisi��es.
    fscanf(requests_file, "%d", &number_of_request_);
    int r1, r2;
    // L� par de requisic�es de tr�fego.
    for (int i = 0; i < number_of_request_; ++i) {
        fscanf(requests_file, "%d %d", &r1, &r2);
        request_.push_back(std::pair<int, int>(r1, r2));
    }
    fclose(requests_file);
}
