#ifndef VERTEX_H
#define VERTEX_H

#include <string.h>
#include <iostream>
#include <cstdlib>
using namespace std;

class Vertex
{
public:
    Vertex();
    Vertex(string name, float longitude, float latitude);
    virtual ~Vertex();
    void setLongitude(float longitude);
    void setLatitude(float latitude);
    void setName(string name);
    float getLongitude();
    float getLatitude();
    string getName();
protected:
private:
    float Longitude, Latitude;
    string Name;
};

#endif // VERTEX_H
