#ifndef PIFRO_GRAPH_H_
#define PIFRO_GRAPH_H_

#include "./Macros.h"
#include "./Vertex.h"

#include <vector>
#include <math.h>

class Graph{
      public:
             Graph();
             explicit Graph(char* filename, int tipo);
             std::vector<Vertex>*& getAdjList();
             int**& getAdjMatrix();
             int getQtVertex();
             void setAdjList(std::vector<Vertex>* adjlist);
             void setQtVertex(int qtvertex);
             void addEdge(int src, int dst, float weight);
             //void addEdge(int src, int dst, float weight);
             void deleteEdge(int vertex);
             std::vector<Vertex>& getNeighbors(int vertex);

             float getTotalCost();
             void cleanCosts();
             void loadFromSNDFile(char* filename);
             void print();
             void printWithWeight();
             void printWithCost();
             void printWithIncCost();
             void printWithQtRequests();

      private:
              std::vector<Vertex>* AdjList;
              int** AdjMatrix;
              int QtVertex;
              int QtEdge;
              //DISALLOW_COPY_AND_ASSIGN(Graph);
};

#endif
