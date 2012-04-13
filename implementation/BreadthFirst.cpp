#include "./BreadthFirst.h"

BreadthFirst::BreadthFirst(){
}

float BreadthFirst::getKmDistance(){
      return KmDistance;
}

std::vector<int> BreadthFirst::getWay(){
      return Way;
}

void BreadthFirst::setKmDistance(float kmdistance){
     KmDistance = kmdistance;
}

void BreadthFirst::setWay(std::vector<int> way){
     Way = way;
}

int BreadthFirst::getQtROADM(std::vector<Vertex>*& adjlist, int src, int dst, int qtvertex){
    
          //Limpando caminho
          Way.clear();
         //todos os vértices brancos
         for(int x=0; x<qtvertex; x++){
             adjlist[x][0].setColor(0);
             adjlist[x][0].setLevel(-1);
             adjlist[x][0].setPrevious(-1);
         }

         adjlist[src][0].setColor(1);
         //DÚVIDA 1 - CONTO O PRIMEIRO NODO COMO UM HOP OU NÃO?
         adjlist[src][0].setLevel(1);
         std::queue<int> q;
         q.push(adjlist[src][0].getNumber());

         int i=1, f=2, act=0, viz=0, iret=-1, wvalue = 0;
         bool found = false;
         std::vector<int> visited;
         
         while(!q.empty()){
                    act = q.front();
                    q.pop();
                    for(int w=0; w<adjlist[act].size();w++){
                            if(adjlist[adjlist[act][w].getNumber()][0].getColor() == 0){
                                 adjlist[adjlist[act][w].getNumber()][0].setColor(1);
                                 adjlist[adjlist[act][w].getNumber()][0].setLevel(adjlist[act][0].getLevel() + 1);
                                 adjlist[adjlist[act][w].getNumber()][0].setPrevious(act);
                                 q.push(adjlist[act][w].getNumber());
                                 visited.push_back(adjlist[act][w].getNumber());
                                 
                            }
                            
                            //ao concluir o caminho até o vértice de destino, faz-se o caminho reverso e amazena-se o caminho
                            if(adjlist[adjlist[act][w].getNumber()][0].getNumber() == dst){
                               adjlist[adjlist[act][w].getNumber()][0].setColor(2);
                               //vértice de destino encontrado, retornará a largura do mesmo
                               iret = adjlist[adjlist[act][w].getNumber()][0].getLevel();
                               found = true;
                               wvalue=w;
                               break;
                            }
                    }
                    if(found){
                         break;
                    }
                    adjlist[act][0].setColor(2);
         }
       
     //Vector com o caminho seguido
     std::vector<int> way;
     way.push_back(dst);
     float km = 0;
     cout.precision(5);
     for(int u=0;u<adjlist[visited[visited.size() - 1]][0].getLevel() - 1;u++){
             way.push_back(adjlist[way[u]][0].getPrevious());
             km += calculateDistance(adjlist[way[u]][0].getNumber(), adjlist[way[u]][0].getPrevious(), adjlist);
             //cout << "Vertice: " << adjlist[way[u]][0].getNumber() << endl;
     }
     setKmDistance(km);
     //sort(way.begin(),way.end());
     setWay(way);
     //cout << "TAMANHO: " << Way.size() << " ";
     return iret;
}

float BreadthFirst::calculateDistance(int src, int dst, std::vector<Vertex>*& adjlist){
    for(int i=0; i<adjlist[src].size(); i++){
            if(adjlist[src][i].getNumber() == dst){
                  return adjlist[src][i].getWeight();
            }
    }
}

void BreadthFirst::printWay(){
     for(int i=(Way.size()-1); i>=0; i--){
             cout << Way[i] << " -> ";
     }
     cout << " TOTAL DISTANCE (KM): " << KmDistance << endl;
}
