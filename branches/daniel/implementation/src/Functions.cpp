#include "Functions.h"

Functions::Functions()
{
    //ctor
}

Functions::~Functions()
{
    //dtor
}

float Functions::fwdm(int w, float l)
{
    float fret = 0, c1 = 0, c2 = 0, c3 = 0;
    //ROADM
    //c1 = (ceilf(w/100) * 2 * ROADMCost); --> Thiago
    c1 = 2 * ROADMCost;
    //OT
    //c2 = (floorf(w * (1 / LOT))); --> Thiago
    //OA
    c2 = (1 / LOA) * OACost;
    //OA
    //c3 = (ceilf(w/100)) * floorf(1/LOA);
    //OT
    c3 = (1 / LOT) * 2 * OTCost;

    fret = c1 * ceil(w / U) + c2 * l * ceil(w / U) + c3 * w * l;

    return fret;
}
