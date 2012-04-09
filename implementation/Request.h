#ifndef PIFRO_REQUEST_H_
#define PIFRO_REQUEST_H_

#include "./Macros.h"

class Request
{
public:

    int Src, Dst, QtROADM, Qt, Id;
    float Distance, Key;

    Request();
    explicit Request(int src, int dst, int qthops, int distance, int qt);
    int getSrc();
    int getDst();
    int getQtROADM();
    float getDistance();
    int getQt();
    float getKey();
    int getId();
    void setSrc(int src);
    void setDst(int dst);
    void setQtROADM(int qtroadm);
    void setDistance(float distance);
    void setQt(int qt);
    void setKey(float key);
    void setId(int id);



private:
};
#endif
