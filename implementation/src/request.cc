// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#include "./request.h"

Request::Request() {
  src_ = 0;
  dst_ = 0;
  qt_roadm_ = 0;
  distance_ = 0;
  qt_ = 0;
}


Request::Request(int src, int dst, int qtroadm, int distance, int qt) {
  src_ = src;
  dst_ = dst;
  qt_roadm_ = qtroadm;
  distance_ = distance;
  qt_ = qt;
}

int Request::GetSrc() {
  return src_;
}

int Request::GetDst() {
  return dst_;
}

int Request::GetQtROADM() {
  return qt_roadm_;
}

float Request::GetDistance() {
  return distance_;
}

int Request::GetQt() {
  return qt_;
}

int Request::GetId() {
  return id_;
}

float Request::GetKey() {
  return key_;
}

void Request::SetSrc(int src) {
  src_ = src;
}

void Request::SetDst(int dst) {
  dst_ = dst;
}

void Request::SetQtROADM(int qtroadm) {
  qt_roadm_ = qtroadm;
}

void Request::SetDistance(float distance) {
  distance_ = distance;
}

void Request::SetQt(int qt) {
  qt_ = qt;
}

void Request::SetKey(float key) {
  key_ = key;
}

void Request::SetId(int id) {
  id_ = id;
}
