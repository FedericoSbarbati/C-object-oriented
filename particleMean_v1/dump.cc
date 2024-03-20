#include <iostream>
#include "Event.h"

void dump( const Event& ev)
{

    std::cout << ev.evNumber << std::endl;
    std::cout << ev.nParticle << std::endl;
    std::cout << ev.x << ' ' << ev.y << ' ' << ev.z << std::endl;

    for (int i = 0; i < ev.nParticle; ++i)
    {
        std::cout << ' ' << ev.part[i]->charge << ' '
             << ev.part[i]->px << ' ' << ev.part[i]->py << ' ' << ev.part[i]->pz << std::endl;
    }
    return;
}