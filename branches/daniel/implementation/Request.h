#ifndef PIFRO_REQUEST_H_
#define PIFRO_REQUEST_H_

#include "./Macros.h"

class Request{
      public:
             Request();
             explicit Request(int src, int dst, int qthops, int distance, int qt);
             int getSrc();
             int getDst();
             int getQtROADM();
             float getDistance();
             float getQt();
             float getKey();
             void setSrc(int src);
             void setDst(int dst);
             void setQtROADM(int qtroadm);
             void setDistance(float distance);
             void setQt(float qt);
             void setKey(float key);
             
             
             
      private:
              int Src, Dst, QtROADM;
              float Distance, Qt, Key;
              
              
};
#endif
