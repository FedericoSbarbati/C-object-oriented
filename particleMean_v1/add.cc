#include <iostream>
#include <fstream>

#include "Event.h"

double mass(const Event *ev);

bool add(const Event& ev, double min, double MAX,double& invMsum, double& squareSum)
{
    double invMass = mass(&ev);
    if( invMass > min && invMass < MAX)
    {
        invMass-= min;
        invMsum += invMass;
        squareSum += (invMass*invMass);

        return true;
    }

    return false;
}