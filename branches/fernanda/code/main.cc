// Copyright 2011 Universidade Federal de Minas Gerais
// Autor: Luiz Gustavo Sathler Dias
// Projeto Orientado em Computação 2

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "./instance.h"

int main(int argc, char* argv[]) {
    char net_file[128];
    char *out_file = NULL;
    bool complete_graph = false;
    int p;
    
    // gera semente aleatoria
    srand(time(NULL));
    
    while ((p = getopt(argc, argv, "a:p:ct:")) != -1) {
        switch(p) {
            case 'a':
                strncpy(net_file, optarg, 128);
                break;
            case 'p':
                out_file = optarg;
                break;
            case 'c':
                complete_graph = true;
                break;
            case 't':
                // usa semente fixa
                srand(atoi(optarg));
            default:
                printf("Invalid parameter\n");
                exit(1);
        }
    }
    //printf("%s %s\n", connections_filename, requests_filename);
    
    Instance::Initialize(net_file);
    Instance *instance = Instance::GetInstance();
    
    instance->Print();
    
    instance->set_complete_graph(complete_graph);
    
    instance->DumpNet(out_file);
    
    delete instance;
    instance = NULL;
    
    return 0;
}
