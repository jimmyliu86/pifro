#include "Vertex.h"

Vertex::Vertex()
{
    //ctor
}

Vertex::Vertex(string name, float longitude, float latitude)
{
    Name = name;
    Longitude = longitude;
    Latitude = latitude;
}

Vertex::~Vertex()
{
    //dtor
}

void Vertex::setLongitude(float longitude)
{
    Longitude = longitude;
}

void Vertex::setLatitude(float latitude)
{
    Latitude = latitude;
}

void Vertex::setName(string name)
{
    Name = name;
}

float Vertex::getLongitude()
{
    return Longitude;
}

float Vertex::getLatitude()
{
    return Latitude;
}

string Vertex::getName()
{
    return Name;
}
