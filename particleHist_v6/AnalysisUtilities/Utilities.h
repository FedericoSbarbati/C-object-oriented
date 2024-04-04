#ifndef Utilities_h
#define Utilities_h

#include <iostream>
#include <cmath>

#include "AnalysisFramework/Event.h"

class Utilities
{
public:
    // compute energy from momentum x,y,z components and invariant mass
    static double energy(double px, double py, double pz, double mass);

    // compute invariant mass from momentum x,y,z components and energy
    static double invariantMass(double px, double py, double pz, double E);
};

#endif
