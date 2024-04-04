#include <iostream>
#include <fstream>

#include "Event.h"

// Function to read an Event object from a file
const Event *read(std::ifstream &file)
{
    Event *ev;     // Pointer to Event object
    int id;        // Event ID
    int nP;        // Number of particles
    float x, y, z; // Event position coordinates

    // Read Event ID
    if (!(file >> id))
    {
        return nullptr; // Return nullptr if unable to read ID
    }

    // Read Event position coordinates
    file >> x >> y >> z;

    // Read number of particles
    file >> nP;

    // Create new Event object
    ev = new Event(id, x, y, z);

    int charge;       // Particle charge
    float px, py, pz; // Particle momentum components

    // Read particle information and add to Event object
    for (int i = 0; i < nP; ++i)
    {
        file >> charge;
        file >> px;
        file >> py;
        file >> pz;
        ev->add(charge, px, py, pz);
    }

    return ev; // Return the Event object
}