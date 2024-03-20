#include <iostream>
#include <fstream>

#include "Event.h"

const Event *read(std::ifstream &file)
{
    Event *ev;
    int id;
    int nP;
    float x, y, z;
    if (!(file >> id))
    {
        return nullptr;
    }
    file >> x >> y >> z;
    file >> nP;

    ev = new Event(id, x, y, z);

    // Allocazione dinamica delle particelle tramite metodo add:
    int charge;
    float px, py, pz;
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