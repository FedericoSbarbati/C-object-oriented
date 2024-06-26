#ifndef EventReadFromFile_h
#define EventReadFromFile_h

#include "AnalysisFramework/EventSource.h"

#include <iostream>
#include <fstream>
#include <string>
class Event;

class EventReadFromFile: public EventSource {

 public:

  // read data from file "name"
  EventReadFromFile( const std::string& name );
  // deleted copy constructor and assignment to prevent unadvertent copy
  EventReadFromFile           ( const EventReadFromFile& x ) = delete;
  EventReadFromFile& operator=( const EventReadFromFile& x ) = delete;

  ~EventReadFromFile() override;

 private:

  // get an event
  const Event* get() override;

  // input file
  std::ifstream* file;

  // read an event
  const Event* readFile();

};

#endif

