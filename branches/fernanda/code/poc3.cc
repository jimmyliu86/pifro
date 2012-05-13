// Copyright 2011 Universidade Federal de Minas Gerais
// Autor: Luiz Gustavo Sathler Dias
// Projeto Orientado em Computação 2

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

#include "graph2.h"
#include "traffic_hand.h"

void help();

int main(int argc, char* argv[]) {
    char *net_file = NULL;
    char *trf_file = NULL;
    char *path_file = NULL;
    char *sol_file = NULL;
    int p = 0;
    
    while ((p = getopt(argc, argv, "a:b:p:s:")) != -1) {
        switch(p) {
            case 'a':
                net_file = strdup(optarg);
                break;
            case 'b':
                trf_file = strdup(optarg);
                break;
            case 'p':
                path_file = strdup(optarg);
                break;
            case 's':
                sol_file = strdup(optarg);
                break;
            default:
                printf("Invalid parameter\n");
                exit(1);
        }
    }
    
    if (net_file && trf_file && path_file && sol_file) {
      TrafficHand traffic_hand(net_file, trf_file, path_file, sol_file);
      traffic_hand.Process();
    } else {
      help(); 
    }
    
    free(net_file);
    free(trf_file);
    free(path_file);
    free(sol_file);
    
    return 0;
}

void help() {
  fprintf(stderr, "Parametros Invalidos.\n"); 
}
