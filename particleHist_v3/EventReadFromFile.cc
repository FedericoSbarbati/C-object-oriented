#include "EventReadFromFile.h"
#include "Event.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// read data from file "name"
EventReadFromFile::EventReadFromFile(const string &name)
{
  file = new ifstream(name.c_str(), ios::binary);
}

EventReadFromFile::~EventReadFromFile()
{
  delete file;
}

// get an event
const Event *EventReadFromFile::get()
{
  return readFile();
}

// read an event
const Event *EventReadFromFile::readFile()
{
  Event *ev;
  int id;
  int nP;
  float x, y, z;

  // Read the event ID
  if (!(*file >> id))
  {
    return nullptr;
  }

  // Read the event position
  *file >> x >> y >> z;

  // Read the number of particles
  *file >> nP;

  // Create a new event object
  ev = new Event(id, x, y, z);

  // Read particle data and add particles to the event
  int charge;
  float px, py, pz;
  for (int i = 0; i < nP; ++i)
  {
    *file >> charge;
    *file >> px;
    *file >> py;
    *file >> pz;
    ev->add(charge, px, py, pz);
  }

  return ev;
}
