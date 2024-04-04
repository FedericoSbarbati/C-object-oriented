#include <iostream>
#include "Event.h"

// Function to dump the event information
void dump(const Event &ev)
{
    // Print the event number
    std::cout << ev.evNumber << std::endl;

    // Print the number of particles
    std::cout << ev.nParticle << std::endl;

    // Print the position of the event
    std::cout << ev.x << ' ' << ev.y << ' ' << ev.z << std::endl;

    // Print the information of each particle
    for (int i = 0; i < ev.nParticle; ++i)
    {
        std::cout << ' ' << ev.part[i]->charge << ' '
                  << ev.part[i]->px << ' ' << ev.part[i]->py << ' ' << ev.part[i]->pz << std::endl;
    }

    return;
}