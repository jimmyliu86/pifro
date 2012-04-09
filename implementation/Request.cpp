#include "Request.h"


Request::Request(){
          Src = 0;
          Dst = 0;
          QtROADM = 0;
          Distance = 0;
          Qt = 0;
}


Request::Request(int src, int dst, int qtroadm, int distance, int qt){
         Src = src;
         Dst = dst;
         QtROADM = qtroadm;
         Distance = distance;
         Qt = qt;
}

int Request::getSrc(){
    return Src;
}

int Request::getDst(){
    return Dst;
}

int Request::getQtROADM(){
    return QtROADM;
}

float Request::getDistance(){
    return Distance;
}

int Request::getQt(){
    return Qt;
}

int Request::getId()
{
    return Id;
}

float Request::getKey(){
      return Key;
}

void Request::setSrc(int src){
     Src = src;
}

void Request::setDst(int dst){
     Dst = dst;
}

void Request::setQtROADM(int qtroadm){
     QtROADM = qtroadm;
}

void Request::setDistance(float distance){
     Distance = distance;
}

void Request::setQt(int qt){
     Qt = qt;
}

void Request::setKey(float key){
     Key = key;
}

void Request::setId(int id)
{
    Id = id;
}
