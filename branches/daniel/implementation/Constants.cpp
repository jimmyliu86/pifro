#include "./Constants.h"

#include <cmath>

Constants::Constants()
{

}

Constants::~Constants()
{

}

float Constants::fwdm(int w, float l)
{
    float fret = 0, c1 = 0, c2 = 0, c3 = 0;
    //ROADM
    c1 = (ceilf(w/100) * 2 * ROADMCost);
    //OT
    c2 = (floorf(w * (1 / LOT)));
    //OA
    c3 = (ceilf(w/100)) * floorf(1/LOA);

    fret = c1 * ceilf(w / U) + c2 * l * ceilf(w / U) + c3 * w * l;

    return fret;
}
