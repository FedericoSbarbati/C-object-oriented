#include "Event.h"

void clear(const Event *ev)
{

    for(int i = 0; i <ev->nParticle; i++)
    {
        delete ev->part[i];
    }
    delete[] ev->part;
    delete ev;

    return;
}