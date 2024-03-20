#ifndef Utilities_h
#define Utilities_h

#include <iostream>
#include <cmath>

#include "Event.h"

/*
Create a Utilities class, and move inside this new class the two functions
computing the energy or the mass from the 3 momentum components and the
mass or the energy, respectively. Declare those functions as "static".
*/

class Utilities
{
public:
    // compute energy from momentum x,y,z components and invariant mass
    static double energy(double px, double py, double pz, double mass);

    // compute invariant mass from momentum x,y,z components and energy
    static double invariantMass(double px, double py, double pz, double E);
};

#endif
