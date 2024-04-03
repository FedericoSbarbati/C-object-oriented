#include "EventReadFromFile.h"

#include "Event.h"
#include "util/include/Input.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// read data from file "name"
EventReadFromFile::EventReadFromFile( const string& name,
                                      ios::openmode mode ) {
  file = InputFactory::create( name, mode );
}


EventReadFromFile::~EventReadFromFile() {
  delete file;
}


// get an event
const Event* EventReadFromFile::get() {
  return readFile();
}


// read an event
const Event* EventReadFromFile::readFile() {

  // event pointer and identifier
  Event* ev;
  int i;

  // try to read input file
  // on success create new event
  if ( *file >> i ) ev = new Event( i );
  // on failure return null pointer
  else return nullptr;

  // read number of points
  int n;
  *file >> n;

  // read and store all points
  int e;
  for ( i = 0; i < n; ++i ) {
    *file >> e;
    ev->add( e );
  }

  return ev;

}

