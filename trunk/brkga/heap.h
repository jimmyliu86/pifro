// Copyright 2011 Universidade Federal de Minas Gerais
// Projeto Orientado em Computação 2
// Classe de definição de Heap.

#ifndef PIFRO_HEAP_H_
#define PIFRO_HEAP_H_

#include <vector>

class HeapMin {
    public:
        HeapMin(std::vector<float>& cost, int length);
        ~HeapMin();
        void MakeHeap();
        void DecreaseKey(int vertex, float new_cost);
        void Print();
        void Heapfy(int i);
        int ExtractMin();
        void Exchange(int i, int j);
        bool Empty();
    private:
        std::vector<float>& cost_;
        std::vector<int> id_;
        std::vector<int> position_;
        int length_;
};

#endif
