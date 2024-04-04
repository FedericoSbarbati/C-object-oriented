#include <iostream>
#include <fstream>

#include "Event.h"

// Function to calculate the mass of an event
double mass(const Event *ev);

// Function to add an event to the sum if its mass is within a given range
bool add(const Event& ev, double min, double MAX, double& invMsum, double& squareSum)
{
    double invMass = mass(&ev);
    if (invMass > min && invMass < MAX)
    {
        invMass -= min;
        invMsum += invMass;
        squareSum += (invMass * invMass);

        return true;
    }

    return false;
}