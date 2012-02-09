#include "./Greedy.h"

//#include <sys/resource.h>

Greedy::Greedy(){
}

void Greedy::setGDemand(Demand& demand){
     GDemand = demand;
}

void Greedy::setGDijkstra(Dijkstra dijkstra){
     GDijkstra = dijkstra;
}

void Greedy::setGGraph(Graph& graph){
     GGraph = graph;
}

Demand Greedy::getGDemand(){
     return GDemand;
}

Dijkstra Greedy::getGDijkstra(){
     return GDijkstra;
}
 
Graph Greedy::getGGraph(){
      return GGraph;
}
          
void Greedy::DemandSort(std::vector<Request>& vecrequest){
   for(int i=0; i<vecrequest.size(); i++){
     //MUDAR SEMENTE
     vecrequest[i].setKey(rand() / static_cast<float>(RAND_MAX));
     //cout << "Nova Chave " << i << ": " << vecrequest[i].getKey() << endl;
   }
   std::sort(vecrequest.begin(), vecrequest.end(), comparison_request_by_key());
}
       
float Greedy::execute(std::vector<Vertex>*& adjlist, std::vector<Request>& vecrequest, int qtvertex, int timeexec){
        
    float telapsed, totalcost;
    double cost, min_cost;

     time_t t1=time(NULL);
     time_t t2=time(NULL);
     
     
    //primeira execução
    totalcost = 0;
    for(int i=0; i<vecrequest.size(); i++){
       totalcost += GDijkstra.getCostByDijkstra(adjlist, qtvertex, vecrequest[i].getSrc(), vecrequest[i].getDst());
    }
    min_cost = 9999999;
    ofstream fout("f:\\greedy_abilene.txt");
    fout << totalcost << ";";
    
    while (true) {
//        GeneratePermutation(request);
//        cost = greedy.Execute(request, 5, 100);

          DemandSort(vecrequest);
          totalcost = 0;
          for(int i=0; i<vecrequest.size(); i++){
             totalcost += GDijkstra.getCostByDijkstra(adjlist, qtvertex, vecrequest[i].getSrc(), vecrequest[i].getDst());
          }
          
          fout << totalcost << ";";
          if (totalcost < min_cost){
             min_cost = totalcost;
          }
          
          t2 = time(NULL);
        // printf("%.4lf\n",telapsed); 10 minutos.
        float totaltime = t2 - t1;
        
        if(totaltime > timeexec) {
            fout.close();
            break;
        }
    }
    return min_cost;
          
}
