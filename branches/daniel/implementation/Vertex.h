#ifndef PIFRO_VERTEX_H_
#define PIFRO_VERTEX_H_

#include "./Macros.h"

class Vertex{
      public:
             explicit Vertex();
             explicit Vertex(int number, int visited, float weight);
             ~Vertex();
             int getNumber();
             int getVisited();
             float getWeight();
             int getColor();
             int getLevel();
             int getPrevious();
             bool getEnabled();
             void setNumber(int number);
             void setVisited(int visited);
             void setWeight(float weight);     
             void setColor(int color);
             void setLevel(int level);
             void setPrevious(int previous);
             void setEnabled(bool enabled);
             
             void setProperties(int number, int visited, float weight);
             void print();
             
      private:
              int Number, Visited, Color, Level, Previous;
              float Weight;
              bool Enabled;
              //DISALLOW_COPY_AND_ASSIGN(Vertex);
};

#endif
