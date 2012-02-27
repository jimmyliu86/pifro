#include "./Vertex.h"

#include <iostream>
#include <cstdlib>
using namespace std;

Vertex::Vertex(){
           Number = -1;
           Visited = -1;
           Weight = -1;
           Color = -1;
           Level = -1;
}

Vertex::Vertex(int number, int visited, float weight){
           Number = number;
           Visited = visited;
           Weight = weight;
           Color = -1;
           Level = -1;
}

Vertex::~Vertex(){
}

int Vertex::getNumber(){
    return Number;
}

int Vertex::getVisited(){
    return Visited;
}

float Vertex::getWeight(){
      return Weight;
}

int Vertex::getColor(){
    return Color;
}

int Vertex::getLevel(){
    return Level;
}

int Vertex::getPrevious(){
    return Previous;
}

float Vertex::getCost()
{
    return Cost;
}

float Vertex::getIncCost()
{
    return IncCost;
}

bool Vertex::getEnabled(){
     return Enabled;
}

void Vertex::setNumber(int number){
     Number = number;
}

void Vertex::setVisited(int visited){
     Visited = visited;
}

void Vertex::setWeight(float weight){
     Weight = weight;
}

void Vertex::setColor(int color){
     Color = color;
}

void Vertex::setLevel(int level){
     Level = level;
}

void Vertex::setProperties(int number, int visited, float weight){
     Number = number;
     Visited = visited;
     Weight = weight;
}

void Vertex::setPrevious(int previous){
     Previous = previous;
}

void Vertex::setCost(float cost)
{
    Cost = cost;
}

void Vertex::setIncCost(float inccost)
{
    IncCost = inccost;
}

void Vertex::setEnabled(bool enabled){
     Enabled = enabled;
}

void Vertex::print(){
     cout << "Vertex Data" << endl;
     cout << "Vertex Number: " << getNumber() << endl;
     cout << "Vertex Visited: " << getVisited() << endl;
     cout << "Vertex Weight: " << getWeight() << endl;
}
