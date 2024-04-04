#include <iostream>
#include <fstream>

#include "Event.h"

// Function to read an Event object from a file
// Returns a pointer to the dynamically allocated Event object
const Event *read(std::ifstream &file)
{
    Event *ev = new Event; // Create a new Event object

    // Read the event number from the file
    if (!(file >> ev->evNumber))
    {
        return nullptr; // Return nullptr if reading fails
    }

    // Read the coordinates of the event
    file >> ev->x >> ev->y >> ev->z;

    // Read the number of particles in the event
    file >> ev->nParticle;

    // Dynamically allocate an array of Particle pointers
    ev->part = new Particle *[ev->nParticle];

    // Read the properties of each particle in the event
    for (int i = 0; i < ev->nParticle; ++i)
    {
        Particle *p = new Particle; // Create a new Particle object

        // Read the charge and momentum components of the particle
        file >> p->charge >> p->px >> p->py >> p->pz;

        ev->part[i] = p; // Assign the Particle object to the array
    }

    return ev; 
}