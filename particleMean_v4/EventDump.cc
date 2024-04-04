#include "EventDump.h"
#include "Event.h"
#include <iostream>

using namespace std;

EventDump::EventDump()
{
}

EventDump::~EventDump()
{
}

// function to be called at execution start
void EventDump::beginJob()
{
  return;
}

// function to be called at execution end
void EventDump::endJob()
{
  return;
}

// function to be called for each event
void EventDump::process(const Event &ev)
{
  // Print the number of particles in the event
  cout << ev.getnParticle() << endl;

  // Print the coordinates of the event
  cout << ev.getX() << ' ' << ev.getY() << ' ' << ev.getZ() << endl;

  // Print the properties of each particle in the event
  for (int i = 0; i < ev.getnParticle(); i++)
  {
    Event::part_ptr p = ev.particle(i);
    cout << ' ' << p->charge << ' '
         << p->px << ' ' << p->py << ' ' << p->pz << endl;
  }

  return;
}
