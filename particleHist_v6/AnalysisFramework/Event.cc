#include "AnalysisFramework/Event.h"

// constructor
Event::Event(int n, float x, float y, float z) : evNumber(n),
                                                 x(x),
                                                 y(y),
                                                 z(z)
// initializations
{
  // reserving memory for particle array
  part.reserve(10);
}

// destructor
Event::~Event()
{
  // delete all the particle pointers
  for (auto p : part)
  {
    // delete the pointers array
    delete p;
  }
  part.clear();
}

void Event::add(int charge, float px, float py, float pz)
{
  // check for the number of particles, if maximum reached do nothing
  // and return
  if (part.size() < part.capacity())
  {
    // create the new particle and fill with data
    Particle *p = new Particle;
    p->charge = charge;
    p->px = px;
    p->py = py;
    p->pz = pz;

    // store the new particle pointer in the array and increase counter
    part.push_back(p); // Control done before capacity increasing to exceed 10 (initial memory reserve)
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
int Event::getnParticle() const
{
  return part.size();
}

// get particle
const Event::Particle *Event::particle(unsigned int i) const
{
  if (i < part.size())
  {
    return part.at(i);
  }
  else
    return nullptr;
}
