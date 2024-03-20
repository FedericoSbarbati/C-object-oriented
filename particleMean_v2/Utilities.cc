#include "Utilities.h"
#include <cmath>

// compute energy from momentum x,y,z components and invariant mass
double Utilities::energy(double px, double py, double pz, double mass)
{
    double en = sqrt(px * px + py * py + pz * pz + mass * mass);
    return en;
}

// compute invariant mass from momentum x,y,z components and energy
double Utilities::invariantMass(double px, double py, double pz, double E)
{
    double invMsqrd = (E * E - (px * px + py * py + pz * pz));
    double invM = invMsqrd > 0 ? sqrt(invMsqrd) : -1;
    return invM;
}