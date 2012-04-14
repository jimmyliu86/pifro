#include "./Graph.h"

Graph::Graph()
{
}
Graph::Graph(char* filename, int tipo)
{
  if(tipo == 0)
  {
    loadFromSNDFile(filename);
  }
}

std::vector<Vertex>*& Graph::getAdjList()
{
  return AdjList;
}

int**& Graph::getAdjMatrix()
{
  return AdjMatrix;
}

int Graph::getQtVertex()
{
  return QtVertex;
}

void Graph::setAdjList(std::vector<Vertex>* adjlist)
{
  AdjList = adjlist;
}

void Graph::setQtVertex(int qtvertex)
{
  QtVertex = qtvertex;
}

void Graph::addEdge(int src, int dst, float weight)
{
  Vertex vsrc(src,0,weight);
  Vertex vdst(dst,0,weight);
  //AdjList[src].push_back(AdjList[dst][0]);
  //AdjList[src][0].setWeight(weight);
  AdjList[src].push_back(vdst);
  //AdjList[dst].push_back(AdjList[src][0]);
  //AdjList[dst][0].setWeight(weight);
  AdjList[dst].push_back(vsrc);
  AdjMatrix[src][dst] = weight;
  AdjMatrix[dst][src] = weight;
}

std::vector<Vertex>& Graph::getNeighbors(int vertex)
{
  return AdjList[vertex];
}

void Graph::loadFromSNDFile(char* filename)
{
  ifstream fin(filename);
  fin >> QtVertex;
  fin >> QtEdge;
  AdjList = new std::vector<Vertex>[QtVertex];
  AdjMatrix = new int*[QtVertex];
  Vertex tmp(0,0,0);
  for(int i=0; i<QtVertex; i++)
  {
    tmp.setNumber(i);
    AdjList[i].push_back(tmp);

    AdjMatrix[i] = new int[QtVertex];
    for(int x=0; x<QtVertex; x++)
    {
      AdjMatrix[i][x] = -1;
    }
  }

  int src = 0, dst = 0;
  float weight = 0;

  for(int i=1; i<QtEdge; i++)
  {
    fin >> src;
    fin >> dst;
    fin >> weight;
    //double weightr = roundIt(weight, pow(10,-2));
    addEdge(src, dst, weight );
  }

  fin.close();
}

float Graph::getTotalCost()
{
  float totalcost = 0;
  for(int p = 0; p < QtVertex; p++)
  {
    for(int x = 1; x < AdjList[p].size(); x++)
    {
      //cout << "TOTALCOST: " << graph.getAdjList()[p][x].getCost() << endl;
      if(AdjList[p][x].getColor() == -1)
      {
        totalcost += AdjList[p][x].getCost();
        AdjList[p][x].setColor(0);
        //Reverso
        //cout << "Somado : " << AdjList[p][0].getNumber() << " - " << AdjList[p][x].getNumber() << " - " << AdjList[p][x].getCost() << endl;
        int u = 1;
        while(u < AdjList[AdjList[p][x].getNumber()].size())
        {
          if(AdjList[AdjList[p][x].getNumber()][u].getNumber() == AdjList[p][0].getNumber())
          {
            AdjList[AdjList[p][x].getNumber()][u].setColor(0);
            //cout << "Ignorando : " << AdjList[AdjList[p][x].getNumber()][0].getNumber() << " - " << AdjList[AdjList[p][x].getNumber()][u].getNumber() << " - Custo:" << AdjList[AdjList[p][x].getNumber()][u].getCost() << endl;
            //break;
          }
          u++;
        }
      }
    }
  }
  cleanColors();

  return totalcost;
}

void Graph::cleanCosts()
{
  for(int i=0; i<QtVertex; i++)
  {
    for(int x=1; x<AdjList[i].size(); x++)
    {
      //cout  << "->" << AdjList[i][x].getWeight() << "->" << "[" << AdjList[i][x].getNumber() << "] ";
      AdjList[i][x].setCost(0);
      AdjList[i][x].setIncCost(0);
    }
    //cout << endl;
  }
}

void Graph::cleanColors()
{
  for(int i=0; i<QtVertex; i++)
  {
    for(int x=1; x<AdjList[i].size(); x++)
    {
      //cout  << "->" << AdjList[i][x].getWeight() << "->" << "[" << AdjList[i][x].getNumber() << "] ";
      AdjList[i][x].setColor(-1);
    }
    //cout << endl;
  }
}

void Graph::print()
{
  for(int i=0; i<QtVertex; i++)
  {
    for(int x=0; x<AdjList[i].size(); x++)
    {
      cout  << "[" << AdjList[i][x].getNumber() << "]->";
    }
    cout << endl;
  }
}

void Graph::printWithWeight()
{
  cout << "ADJLIST:" << endl << endl;
  for(int i=0; i<QtVertex; i++)
  {
    cout << "[" << AdjList[i][0].getNumber() << "]";
    for(int x=1; x<AdjList[i].size(); x++)
    {
      cout  << "->" << AdjList[i][x].getWeight() << "->" << "[" << AdjList[i][x].getNumber() << "] ";
    }
    cout << endl;
  }

  cout << endl << endl << "ADJMATRIX:" << endl << endl;
  cout << "     ";
  for(int i=0; i<QtVertex; i++)
  {
    cout << "\t[" << i << "]";
  }
  cout << endl;

  for(int i=0; i<QtVertex; i++)
  {
    cout << "[" << i << "]";
    for(int x=0; x<QtVertex; x++)
    {
      cout << "\t" << AdjMatrix[i][x];
    }
    cout << endl;
  }

}

void Graph::printWithCost()
{
  cout << endl << endl << "ADJLIST:" << endl << endl;
  for(int i=0; i<QtVertex; i++)
  {
    cout << "[" << AdjList[i][0].getNumber() << "]";
    for(int x=1; x<AdjList[i].size(); x++)
    {
      cout  << "->" << AdjList[i][x].getCost() << "->" << "[" << AdjList[i][x].getNumber() << "] ";
    }
    cout << endl;
  }

  /*cout << endl << endl << "ADJMATRIX:" << endl << endl;
  cout << "     ";
  for(int i=0; i<QtVertex; i++)
  {
      cout << "\t[" << i << "]";
  }
  cout << endl;

  for(int i=0; i<QtVertex; i++)
  {
      cout << "[" << i << "]";
      for(int x=0; x<QtVertex; x++)
      {
          cout << "\t" << AdjMatrix[i][x];
      }
      cout << endl;
  }*/

}

void Graph::printWithIncCost()
{
  cout << endl << endl << "ADJLIST:" << endl << endl;
  for(int i=0; i<QtVertex; i++)
  {
    cout << "[" << AdjList[i][0].getNumber() << "]";
    for(int x=1; x<AdjList[i].size(); x++)
    {
      cout  << "->" << AdjList[i][x].getIncCost() << "->" << "[" << AdjList[i][x].getNumber() << "] ";
    }
    cout << endl;
  }

  /*cout << endl << endl << "ADJMATRIX:" << endl << endl;
  cout << "     ";
  for(int i=0; i<QtVertex; i++)
  {
      cout << "\t[" << i << "]";
  }
  cout << endl;

  for(int i=0; i<QtVertex; i++)
  {
      cout << "[" << i << "]";
      for(int x=0; x<QtVertex; x++)
      {
          cout << "\t" << AdjMatrix[i][x];
      }
      cout << endl;
  }*/

}

void Graph::printWithQtRequests()
{
  cout << endl << endl << "ADJLIST:" << endl << endl;
  for(int i=0; i<QtVertex; i++)
  {
    cout << "[" << AdjList[i][0].getNumber() << "]";
    for(int x=1; x<AdjList[i].size(); x++)
    {
      cout  << "->" << AdjList[i][x].getQtRequests() << "->" << "[" << AdjList[i][x].getNumber() << "]";
    }
    cout << endl;
  }

  /*cout << endl << endl << "ADJMATRIX:" << endl << endl;
  cout << "     ";
  for(int i=0; i<QtVertex; i++)
  {
      cout << "\t[" << i << "]";
  }
  cout << endl;

  for(int i=0; i<QtVertex; i++)
  {
      cout << "[" << i << "]";
      for(int x=0; x<QtVertex; x++)
      {
          cout << "\t" << AdjMatrix[i][x];
      }
      cout << endl;
  }*/

}
