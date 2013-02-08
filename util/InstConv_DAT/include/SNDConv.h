#ifndef SNDCONV_H
#define SNDCONV_H

#include "Request.h"
#include "Vertex.h"

#include <vector>
#include <math.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string.h>
using namespace std;

#define pi 3.14159265358979323846

class SNDConv
{
public:
    SNDConv();
    SNDConv(char* filename);
    virtual ~SNDConv();
    void ConvertFile();
    double distance(double lat1, double lon1, double lat2, double lon2, char unit);
    double rad2deg(double rad);
    double deg2rad(double deg);
protected:
private:
    char* Filename;
};

#endif // SNDCONV_H
