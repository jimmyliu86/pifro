// Copyright 2011 Universidade Federal de Minas Gerais
// Autor: Luiz Gustavo Sathler Dias
// Projeto Orientado em Computação 2
// Classe de implementação de instância.

#include "./instance.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <queue>

Instance* Instance::instance_ = NULL;

Instance::Instance() {
}

Instance::~Instance() {
    delete g_;
    delete[] instance_name_;
}

void Instance::Initialize(const char* connections_filename,
                          const char* requests_filename) {
    // Inicializa construtor.
    instance_ = new Instance();
    // Lê dados da instância.
    instance_->ExtractInstanceName(connections_filename);
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
    std::vector<Request>::iterator it;
    for (it = request_.begin(); it != request_.end(); ++it)
        printf("%d %d\n", it->src, it->dst);
}

int Instance::GetNumberOfRequest() const {
    return number_of_request_;
}

Graph* Instance::GetGraph() {
    return g_;
}

const std::vector<Request>& Instance::GetRequest() const {
    return request_;
}

// Lê arquivo com as conexões existentes na rede.
void Instance::ReadConnectionsFile(const char* connections_filename) {
    FILE* connections_file = fopen(connections_filename, "r");
    if (connections_file == NULL) {
        printf("file %s not found\n", connections_filename);
        exit(1);
    }
    // Lê número de nós e número de conexões
    fscanf(connections_file, "%d %d", &number_of_node_, &number_of_edge_);
    // Inicializa grafo.
    g_ = new Graph(number_of_node_);
    int n1, n2;
    float weight;
    // Adiciona conexões no grafo que representa a topologia da rede.
    for (int i = 0; i < number_of_edge_; ++i) {
        if (instance_type_ == NET_TYPE) {
            fscanf(connections_file, "%d %d", &n1, &n2);
            g_->AddEdge(n1, n2);
        }
        else if (instance_type_ == SND_TYPE) {
            fscanf(connections_file, "%d %d %f", &n1, &n2, &weight);
            g_->AddEdge(n1, n2);
            g_->AddEdge(n2, n1);
        }
    }
    fclose(connections_file);
}

// Lê arquivo com as requisicões de tráfego.
void Instance::ReadRequestsFile(const char* requests_filename) {
    FILE* requests_file = fopen(requests_filename, "r");
    if (requests_file == NULL) {
        printf("file %s not found\n", requests_filename);
        exit(1);
    }

    // Lê número de requisições.
    fscanf(requests_file, "%d", &number_of_request_);
    int r1, r2;
    Request r;
    request_.reserve(number_of_request_);
    // Lê par de requisicões de tráfego.
    for (int i = 0; i < number_of_request_; ++i) {
        fscanf(requests_file, "%d %d", &r.src, &r.dst);
        r.id = i;
        request_.push_back(r);
    }

    fclose(requests_file);
}

void Instance::CalculateHops() {
    for (int i = 0; i < number_of_request_; ++i)
        BreadthFirst(request_[i]);
}

void Instance::BreadthFirst(Request& i) {
    std::queue<int> Q;
    std::vector<int> level;
    std::vector<bool> visited;
    level.reserve(number_of_node_);
    visited.reserve(number_of_node_);
    for (int j = 0; j < number_of_node_; ++j) {
        level.push_back(0);
        visited.push_back(false);
    } 
    
    // Empilhar vértice i.src.
    Q.push(i.src);
    visited[i.src] = true;
    int top;
    std::list<int> neighbors;
    std::list<int>::iterator it;
    while(!Q.empty()) {
        top = Q.front();
        Q.pop();
        neighbors = g_->GetNeighbors(top);
        for (it = neighbors.begin(); it != neighbors.end(); ++it) {
            if (!visited[*it]) {
                // Se encontrou destino retornar.
                if (*it == i.dst) {
                    level[i.dst] = level[top] + 1;
                    i.hop = level[i.dst];
                    return;
                }
                else {
                    visited[*it] = true;
                    level[*it] = level[top] + 1;
                    Q.push(*it);
                }
            }
        }
    }
    return;
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
    else if (strcmp(extension, "snd") == 0)
        instance_type_ = SND_TYPE;
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
