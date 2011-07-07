// Copyright 2011 Universidade Federal de Minas Gerais
// Autor: Luiz Gustavo Sathler Dias
// Projeto Orientado em Computação 2

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "./instance.h"
#include "./tester.h"

int main(int argc, char* argv[]) {
    char connections_filename[128];
    char requests_filename[128];
    int p;
    while ((p = getopt(argc, argv, "n:t:")) != -1) {
        switch(p) {
            case 'n':
                strcpy(connections_filename, optarg);
                break;
            case 't':
                strcpy(requests_filename, optarg);
                break;
            default:
                printf("Invalid parameter\n");
                exit(1);
        }
    }
    //printf("%s %s\n", connections_filename, requests_filename);
    srand(time(NULL));
    Instance::Initialize(connections_filename, requests_filename);
    Instance *instance = Instance::GetInstance();
    instance->CalculateHops();
    //Heuristic heuristic;
    //heuristic.Execute(instance->GetRequest(), 0, 100);
    Tester test;
    test.Initialize(instance);
    test.Execute(GENETICA);
    //test.Execute(PSC_T);
    return 0;
}
