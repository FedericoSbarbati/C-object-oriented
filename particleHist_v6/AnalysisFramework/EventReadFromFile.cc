#include "AnalysisFramework/EventReadFromFile.h"
#include "AnalysisFramework/Event.h"

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
  if (!(*file >> id))
  {
    return nullptr;
  }
  *file >> x >> y >> z;
  *file >> nP;

  ev = new Event(id, x, y, z);

  // Allocazione dinamica delle particelle tramite metodo add:
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
