#include <iostream>
#include "Event.h"

// Function to print the details of an Event
void dump(const Event &ev)
{
    // Print the event number
    std::cout << ev.evNumber << std::endl;

    // Print the number of particles in the event
    std::cout << ev.nParticle << std::endl;

    // Print the x, y, z coordinates of the event
    std::cout << ev.x << ' ' << ev.y << ' ' << ev.z << std::endl;

    // Loop over each particle in the event
    for (int i = 0; i < ev.nParticle; ++i)
    {
        // Print the charge and momentum components of the particle
        std::cout << ' ' << ev.part[i]->charge << ' '
                  << ev.part[i]->px << ' ' << ev.part[i]->py << ' ' << ev.part[i]->pz << std::endl;
    }

    return;
}