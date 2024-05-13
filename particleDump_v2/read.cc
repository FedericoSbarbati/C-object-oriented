#include <iostream>
#include <fstream>

#include "Event.h"

const Event *read(std::ifstream &file)
{
    // Create a new Event object (Dynamic memory allocation)
    Event *ev = new Event;

    // Read the event number from the file
    // If reading fails (e.g., end of file reached), return nullptr
    if (!(file >> ev->evNumber))
    {
        return nullptr;
    }

    // Read the x, y, z coordinates from the file
    file >> ev->x >> ev->y >> ev->z;

    // Read the number of particles from the file
    file >> ev->nParticle;

    // Allocate memory for the particles
    ev->part = new Particle *[ev->nParticle];

    // Loop over each particle
    for (int i = 0; i < ev->nParticle; ++i)
    {
        // Create a new Particle object
        Particle *p = new Particle;

        // Read the charge and momentum components from the file
        file >> p->charge;
        file >> p->px;
        file >> p->py;
        file >> p->pz;

        // Store the particle in the event
        ev->part[i] = p;
    }

    // Return the populated Event object
    return ev;
}