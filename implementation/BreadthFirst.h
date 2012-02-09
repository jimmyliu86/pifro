#ifndef PIFRO_BREADTHFIRST_H_
#define PIFRO_BREADTHFIRST_H_

#include "./Macros.h"
#include "./Vertex.h"

#include <vector>
#include <queue>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <queue>

using namespace std;

class BreadthFirst{
      
      public:
              BreadthFirst();
              float getKmDistance();
              std::vector<int> getWay();
              void setKmDistance(float kmdistance);
              void setWay(vector<int> way);
              int getQtROADM(std::vector<Vertex>*& adjlist, int src, int dst, int qtvertex);
              float calculateDistance(int src, int dst, std::vector<Vertex>*& adjlist);
              
              void printWay();
      private:
              float KmDistance;
              std::vector<int> Way;
             
};

#endif
