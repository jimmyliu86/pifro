#ifndef PIRFRO2_CONSTANTS_H
#define PIFRO2_CONSTANTS_H

#include <vector>
#include <cmath>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <queue>
#include <time.h>
#include <string.h>
#include <algorithm>

using namespace std;

//const float ROADMCost = 20000000; /* ROADM Price */
const float ROADMCost = 500000; /* ROADM Price */
const float OACost = ROADMCost / 2; /* Optical Amplifier Price */
const float OTCost = ROADMCost * 0.10; /* Optical Transponder Price */
const float LOA = 100; /* Distance for install Optical Amplifier (KM) */
const float LOT = 500; /* Distance for install Optical Transponder (aproximative valeu by Antonakopoulos and Zhang */
const float U = 100; /* Demands suported per fiber */

#endif // PIFRO2_CONSTANTS_H
