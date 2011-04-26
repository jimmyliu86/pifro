/*
    Copyright 2011 Luiz Gustavo Sathler Dias
    Projeto Orientado em Computacao 2
    Classe de definicao de heap
*/

#ifndef HEAP_H_
#define HEAP_H_

class HeapMin {
    public:
        HeapMin(float *cost, int length);
        ~HeapMin();
        void MakeHeap();
        void DecreaseKey(int vertex, float new_cost);
        void Print();
        void Heapify(int i);
        int GetMin();
        void Exchange(int i, int j);
        bool Empty();
    private:
        float *cost_;
        int *id_;
        int *index_;
        int length_;
};

#endif
