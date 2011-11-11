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
    char alg[128];
    int p;
    while ((p = getopt(argc, argv, "n:t:a:")) != -1) {
        switch(p) {
            case 'n':
                strcpy(connections_filename, optarg);
                break;
            case 't':
                strcpy(requests_filename, optarg);
                break;
            case 'a':
                strcpy(alg, optarg);
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
    Tester test;
    test.Initialize(instance);

    if (strcmp(alg, "PSC") == 0) {
      test.Execute(PSC_T);
    } else if (strcmp(alg, "MS-PSC") == 0) {
      test.Execute(PSC);
    } else if (strcmp(alg, "GA") == 0) {
       test.Execute(GENETICA);
    } else {
      printf("Você esqueceu o -a [GA:PSC]\n");
    }
    return 0;
}
