#ifndef PIFRO2_VERTEX_H_
#define PIFRO2_VERTEX_H_

#include "./Macros.h"

class Vertex {
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
  float getCost();
  float getIncCost();
  bool getEnabled();
  int getQtRequests();

  void setNumber(int number);
  void setVisited(int visited);
  void setWeight(float weight);
  void setColor(int color);
  void setLevel(int level);
  void setPrevious(int previous);
  void setCost(float cost);
  void setIncCost(float inccost);
  void setEnabled(bool enabled);
  void setQtRequests(int qtrequests);

  void setProperties(int number, int visited, float weight);
  void print();

private:
  int Number, Visited, Color, Level, Previous, QtRequests;
  float Weight, Cost, IncCost;
  bool Enabled;
  //DISALLOW_COPY_AND_ASSIGN(Vertex);
};

#endif //PIFRO2_VERTEX_H_
