// Copyright 2012 CEFET MG
// Autor: Daniel Morais dos Reis
// Implementacao dos experimentos para PIFRO

#ifndef _PIFRO2_INCLUDE_CONSTANTS_H_
#define _PIFRO2_INCLUDE_CONSTANTS_H_

//  ROADM Price
const float ROADMCost = 500000;
//  Optical Amplifier Price
const float OACost = ROADMCost / 2;
//  Optical Transponder Price
const float OTCost = ROADMCost * 0.10;
//  Distance for install Optical Amplifier (KM)
const float LOA = 100;
//  Distance for install Optical Transponder
//  (aproximative value by Antonakopoulos and Zhang)
const float LOT = 500;
//  Demands suported per fiber
const float U = 100;

#endif  // _PIFRO2_INCLUDE_CONSTANTS_H_
