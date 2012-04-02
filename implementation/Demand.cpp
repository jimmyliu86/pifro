#include "./Demand.h"
#include "./BreadthFirst.h"

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <queue>
#include <vector>
#include <algorithm>

#include "./Comparision.h"
using namespace std;


Demand::Demand(){
}

Demand::Demand(char* filename, int tipo, std::vector<Vertex>*& adjlist, int qtvertex){
         if(tipo == 0){
                 loadFromTRFFile(filename, adjlist, qtvertex);
         }
}

std::vector<Request>& Demand::getVecRequest(){
     return VecRequest;
}

void Demand::setVecRequest(std::vector<Request> vecrequest){
     VecRequest = vecrequest;
}

int Demand::getQtRequest(){
    return QtRequest;
}

void Demand::setQtRequest(int qtrequest){
     QtRequest = qtrequest;
}

/*bool Demand::compare(Request request1, Request request2){
     return (request1.getQtROADM() < request2.getQtROADM());
}*/

void Demand::loadFromTRFFile(char* filename, std::vector<Vertex>*& adjlist, int qtvertex){
     ifstream fin(filename);
     fin >> QtRequest;
     Request request;
     int src, dst;
     int qt;

     //=====>BreadthFirst bfs;

     vector<int> visited;

     for(int i=0; i<QtRequest; i++){
             fin >> src;
             fin >> dst;
             fin >> qt;

             request.setSrc(src);
             request.setDst(dst);
             request.setQt(qt);
             //====>request.setQtROADM(bfs.getQtROADM(adjlist, src, dst, qtvertex));
             //cout << "SRC: " << src << " - DST: " << dst << " - ";
// ------>>> bfs.printWay();
             //cout << "======================================\n";
             //cout << "QTROADM: " << request.getQtROADM() << " - i: " << i << endl;
             VecRequest.push_back(request);
     }
     fin.close();

     //bfs.getQtROADM(adjlist, 5, 10, qtvertex);
     //bfs.printWay();
     //====>>>>sort(VecRequest.begin(), VecRequest.end(), comparison_request_by_qtroadm());
     //cout << "QT: " << VecRequest.begin().getQtROADM()<<endl;
}

void Demand::print(){
     for(int i=0; i<VecRequest.size(); i++){
             cout << "Source: " << VecRequest[i].getSrc() << " - Destination: " << VecRequest[i].getDst() << " - Quantity: " << VecRequest[i].getQt() << " - QtROADM: " << VecRequest[i].getQtROADM() << endl;
     }
}
