#include "Graph.h"

Graph::Graph()
{
    //ctor
}

Graph::~Graph()
{
    //dtor
}

void Graph::addVertex(string name, float longitude, float latitude)
{
    Vertex v(name, longitude, latitude);
    VecVertex.push_back(v);
}

void Graph::print()
{
    for(int i=0; i<VecVertex.size(); i++)
    {
        cout << "Name: " << VecVertex[i].getName() << " - Longitude: " << VecVertex[i].getLongitude() << " - Latitude: " << VecVertex[i].getLatitude() << "\n";
    }
}
