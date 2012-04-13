#ifndef PIFRO_DEMAND_H_
#define PIFRO_DEMAND_H_

#include "./Macros.h"
#include "./Request.h"
#include "./Graph.h"

#include <vector>

class Demand{
      public:
             Demand();
             explicit Demand(char* filename, int tipo, std::vector<Vertex>*& adjlist, int qtvertex);             
             std::vector<Request>& getVecRequest();
             void setVecRequest(std::vector<Request> vecrequest);
             int getQtRequest();
             void setQtRequest(int qtrequest);
             
             void loadFromTRFFile(char* filename, std::vector<Vertex>*& adjlist, int qtvertex);
             //bool compare(Request request1, Request request2);
             int qtROADMByBFS(std::vector<Vertex>*& adjlist, int src, int dst, int qtvertex);
             void print();
      
      private:
              std::vector<Request> VecRequest;              
              int QtRequest;
};

#endif
