#ifndef REQUEST_H
#define REQUEST_H

#include <string.h>
#include <iostream>
#include <cstdlib>
using namespace std;

class Request
{
public:
    Request();
    virtual ~Request();
    string getSrc();
    string getDst();
    int getIsrc();
    int getIdst();
    double getQt();
    void setSrc(string src);
    void setDst(string dst);
    void setIsrc(int isrc);
    void setIdst(int idst);
    void setQt(double qt);

protected:
private:
    string Src, Dst;
    int Isrc, Idst;
    double Qt;
};

#endif // REQUEST_H
