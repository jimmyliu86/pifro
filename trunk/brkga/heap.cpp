/*
    Copyright 2011 Luiz Gustavo Sathler Dias
    Projeto Orientado em Computacao 2
    Classe com implementacao de heap minimo
*/

#include "heap.h"

#include <stdio.h>

HeapMin::HeapMin(float *cost, int length)
    : cost_(cost), length_(length) {
    this->index_ = new int[length_];
    this->id_ = new int[length_];
    for (int i = 0; i < length_; ++i) {
        id_[i] = i;
        index_[i] = i;
    }
}

void HeapMin::Exchange(int i, int j) {
    float swap_cost;
    int swap_id;

    // swap_cost = cost_[i];
    // cost_[i] = cost_[j];
    // cost_[j] = swap_cost;
    swap_id = id_[i];
    index_[id_[i]] = j;
    index_[id_[j]] = i;
    id_[i] = id_[j];
    id_[j] = swap_id;
}

void HeapMin::MakeHeap() {
    for (int i = ((length_ - 2) / 2); i >= 0; --i)
        Heapify(i);
}

void HeapMin::Heapify(int i) {
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
        // chama refaz para filho trocado
        Heapify(smaller);
    }
}

int HeapMin::GetMin() {
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
    index_[id_[0]] = 0;
    length_--;
    Heapify(0);
    return min_id;
}

void HeapMin::DecreaseKey(int vertex, float new_cost) {
    int i = index_[vertex];
    int x = id_[i];
    cost_[x] = new_cost;
    while (i>0 && cost_[id_[(i - 1) / 2]] >= cost_[x]) {
        Exchange(i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

bool HeapMin::Empty() {
    return (this->length_ == 0);
}

void HeapMin::Print() {
    for (int i = 0; i < length_; ++i)
        printf("%f : %d\n", cost_[i], id_[i]);
}

HeapMin::~HeapMin() {
    delete[] id_;
    delete[] index_;
}
