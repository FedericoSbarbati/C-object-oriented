#include <iostream>
#include <fstream>

#include "Event.h"

// Function to read an Event object from a file
// Returns a pointer to the dynamically allocated Event object
// Returns nullptr if the file is empty or if there was an error reading the data
const Event *read(std::ifstream &file)
{
    Event *ev; // Pointer to the Event object
    int id; // Event ID
    int nP; // Number of particles
    float x, y, z; // Event coordinates

    // Read the Event ID from the file
    if (!(file >> id))
    {
        return nullptr;
    }

    // Read the Event coordinates from the file
    file >> x >> y >> z;

    // Read the number of particles from the file
    file >> nP;

    // Create a new Event object with the read data
    ev = new Event(id, x, y, z);

    // Read the particle data and add particles to the Event object
    int charge; // Particle charge
    float px, py, pz; // Particle momentum components
    for (int i = 0; i < nP; ++i)
    {
        file >> charge;
        file >> px;
        file >> py;
        file >> pz;
        ev->add(charge, px, py, pz);
    }

    return ev;
}