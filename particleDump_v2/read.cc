#include <iostream>
#include <fstream>

#include "Event.h"

const Event *read(std::ifstream &file)
{
    Event *ev = new Event;
    if (!(file >> ev->evNumber))
    {
        return nullptr;
    }
    file >>ev->x >> ev->y >> ev->z;
    file >> ev->nParticle;

    //Allocazione dinamica delle particelle:
    ev->part = new Particle* [ev->nParticle];
    for(int i = 0; i < ev->nParticle; ++i)
    {
        Particle *p = new Particle;
        file >> p->charge;
        file >> p->px;
        file >> p->py;
        file >> p->pz;

        ev->part[i] = p;
    }

    return ev;
}