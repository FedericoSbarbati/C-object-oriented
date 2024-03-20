#include "Event.h"

// Setting the max number of particles
const unsigned int Event::maxSize = 10;

// constructor
Event::Event(int n, float x, float y, float z) : evNumber(n),
                                                 x(x),
                                                 y(y),
                                                 z(z)
// initializations
{
  nParticle = 0;
  // allocate a buffer for particle pointers
  part = new Particle *[maxSize];
  for (unsigned int i = 0; i < maxSize; ++i)
  {
    Particle *p = new Particle;
    part[i] = p;
  }
}

// destructor
Event::~Event()
{
  // delete all the particle pointers
  for (unsigned int i = 0; i < maxSize; ++i)
  {
    // delete the pointers array
    delete part[i];
  }
  delete[] part;
}

void Event::add(int charge, float px, float py, float pz)
{
  // check for the number of particles, if maximum reached do nothing
  // and return
  if ( nParticle < maxSize)
  {
    // create the new particle and fill with data
    Particle *p = new Particle;
    p->charge = charge;
    p->px = px;
    p->py = py;
    p->pz = pz;

    // store the new particle pointer in the array and increase counter
    part[nParticle] = p;
    nParticle++;
  }
  return;
}

// get event id.
int Event::eventNumber() const
{
  return evNumber;
}
// get decay point coordinates
float Event::getX() const
{
  return x;
}
float Event::getY() const
{
  return y;
}
float Event::getZ() const
{
  return z;
}

// get number of particles
int Event::getnParticle() const
{
  return nParticle;
}
// get particle
const Event::Particle *Event::particle(unsigned int i) const
{
  if (i < (unsigned int) nParticle)
  {
    return part[i];
  }
  else return nullptr;
}
