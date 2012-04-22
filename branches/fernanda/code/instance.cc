// Copyright 2011 Universidade Federal de Minas Gerais
// Autor: Luiz Gustavo Sathler Dias
// Projeto Orientado em Computação 2
// Classe de implementação de instância.

#include "./instance.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <queue>

Instance* Instance::instance_ = NULL;

Instance::Instance() {
    g_ = NULL;
    instance_name_ = NULL;
    complete_graph_ = false;
}

Instance::~Instance() {
    delete g_;
    free(instance_name_);
    instance_name_ = NULL;
}

void Instance::Initialize(const char* connections_filename) {
    // Inicializa construtor.
    instance_ = new Instance();
    // Lê dados da instância.
    instance_->ExtractInstanceName(connections_filename);
    instance_->ReadConnectionsFile(connections_filename);
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
    printf("Topology:\n");
    g_->Print();
}

Graph* Instance::GetGraph() {
    return g_;
}

// Lê arquivo com as conexões existentes na rede.
void Instance::ReadConnectionsFile(const char* connections_filename) {
    FILE* connections_file = fopen(connections_filename, "r");
    if (connections_file == NULL) {
        printf("file %s not found\n", connections_filename);
        exit(1);
    }
    
    if (instance_type_ == NET_TYPE) {
         // Lê número de nós e número de conexões
         fscanf(connections_file, "%d %d", &number_of_node_, &number_of_edge_);
    }
    
    if (instance_type_ == TRF_TYPE) {
         // Lê número de nós e número de conexões
         fscanf(connections_file, "%d", &number_of_edge_);
         number_of_node_ = (1 + sqrt(number_of_edge_*8 + 1))/2;
    }
    
    // Inicializa grafo.
    g_ = new Graph(number_of_node_);
    int n1, n2;
    float weight;
    // Adiciona conexões no grafo que representa a topologia da rede.
    for (int i = 0; i < number_of_edge_; ++i) {
        if (instance_type_ == NET_TYPE) {
            fscanf(connections_file, "%d %d %f", &n1, &n2, &weight);
            g_->AddEdge(n1, n2);
            g_->AddEdge(n2, n1);
            g_->SetCost(n1, n2, 1);
            g_->SetCost(n2, n1, 1);
        }
        else if (instance_type_ == TRF_TYPE) {
            fscanf(connections_file, "%d %d %f", &n1, &n2, &weight);
            g_->AddEdge(n1, n2);
            g_->AddEdge(n2, n1);
            g_->SetCost(n1, n2, 1);
            g_->SetCost(n2, n1, 1);
        }
    }
    fclose(connections_file);
}

void Instance::ExtractInstanceName(const char* filename) {
    char tmp[30], extension[10];
    sscanf(filename, "%s", tmp);
    int length = strlen(tmp);
    int newlength = length;
    // Identifica extensão.
    length -= 4;
    int j = 0;
    for (int i = length+1; i < newlength; ++i) {
        extension[j] = tmp[i];
        ++j;
    }
    extension[j] = '\0';
    if (strcmp(extension,"net") == 0)
        instance_type_ = NET_TYPE;
    else if (strcmp(extension, "trf") == 0)
        instance_type_ = TRF_TYPE;
    else
        printf("invalid instance type\n");
    // Recupera nome da instância sem extensão. 
    tmp[length] = '\0';
    instance_name_ = strdup(tmp);

    //printf("%s %s\n", instance_name_, extension);
}

const char* Instance::GetName() const {
    return instance_name_;
}

void Instance::DumpNet(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("unable to create file %s\n", filename);
        // FIXME(fernanda) fix this
        exit(1);
    }

    if (instance_type_ == NET_TYPE) {
         // Lê número de nós e número de conexões
         fprintf(file, "%d %d\n", number_of_node_, (complete_graph_) ? 
            number_of_node_*(number_of_node_ - 1)/2 : number_of_edge_);
    }
    
    if (instance_type_ == TRF_TYPE) {
         // Lê número de nós e número de conexões
         fprintf(file, "%d\n", number_of_edge_);
    }
    
    // Adiciona conexões no grafo que representa a topologia da rede.
    for (int i = 0; i < number_of_node_; ++i) {
        for (int j = i + 1; j < number_of_node_; ++j) {
            if (instance_type_ == NET_TYPE) {
                if (complete_graph_ || g_->IsEdge(i, j)) {
                    fprintf(file, "%d %d %d\n", i, j, static_cast<int>(rand()%99) + 1);
                }
            }
            else if (instance_type_ == TRF_TYPE) {
                if (complete_graph_ || g_->IsEdge(i, j)) {
                    fprintf(file, "%d %d %d\n", i, j, static_cast<int>(rand()%99) + 1);
                }
            }
        }
    }
    fclose(file);
    file = NULL;
}

void Instance::set_complete_graph(bool enable) {
    complete_graph_ = enable;
}

bool Instance::complete_graph() const {
    return complete_graph_;
}
