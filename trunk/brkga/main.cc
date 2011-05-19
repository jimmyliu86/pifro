// Copyright 2011 Universidade Federal de Minas Gerais

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "./instance.h"
#include "./heuristic.h"

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
    printf("%s %s\n", connections_filename, requests_filename);
    Instance::Initialize(connections_filename, requests_filename);
    Heuristic heuristic;
    heuristic.Execute(0, 10);
    return 0;
}
