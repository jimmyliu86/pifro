// Copyright 2011 Universidade Federal de Minas Gerais
// Autor: Luiz Gustavo Sathler Dias
// Projeto Orientado em Computação 2
// Implementação da classe Heap.

#include "heap.h"
#include <stdio.h>

HeapMin::HeapMin(std::vector<float>& cost, int length) : cost_(cost),
length_(length) {
    position_.resize(length);
    id_.resize(length);
    for (int i = 0; i < length; ++i) {
        id_[i] = i;
        position_[i] = i;
    }
}

void HeapMin::Exchange(int i, int j) {
    float swap_cost;
    int swap_id;

    // swap_cost = cost_[i];
    // cost_[i] = cost_[j];
    // cost_[j] = swap_cost;
    swap_id = id_[i];
    position_[id_[i]] = j;
    position_[id_[j]] = i;
    id_[i] = id_[j];
    id_[j] = swap_id;
}

void HeapMin::MakeHeap() {
    for (int i = ((length_ - 1) / 2); i >= 0; --i)
        Heapfy(i);
}

void HeapMin::Heapfy(int i) {
    int left, right;
    int smaller;

    left = 2*i + 1;
    right = 2*i + 2;

    if (left < length_ &&  cost_[id_[left]] < cost_[id_[i]])
        smaller = left;
    else
        smaller = i;
    if (right < length_ && cost_[id_[right]] < cost_[id_[smaller]])
        smaller = right;
    if (smaller != i) {
        Exchange(i, smaller);
        // chama refaz para filho trocado.
        Heapfy(smaller);
    }
}

int HeapMin::ExtractMin() {
    if (length_ < 1) {
        printf("heap overflow\n");
        return -1;
    }
    int min_id;

    // mincost = cost[0];
    // *cmin = mincost;
    min_id = id_[0];
    // cost_[0] = cost_[length_ - 1];
    id_[0] = id_[length_ - 1];
    position_[id_[0]] = 0;
    length_--;
    Heapfy(0);
    return min_id;
}

void HeapMin::DecreaseKey(int vertex, float new_cost) {
    int i = position_[vertex];
    int x = id_[i];
    cost_[x] = new_cost;
    while (i>0 && cost_[id_[(i - 1) / 2]] > cost_[x]) {
        Exchange(i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

bool HeapMin::Empty() {
    return (length_ == 0);
}

void HeapMin::Print() {
    for (int i = 0; i < length_; ++i)
        printf("%f : %d\n", cost_[i], id_[i]);
}

HeapMin::~HeapMin() {
}
