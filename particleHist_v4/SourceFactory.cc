#include "SourceFactory.h"
#include "AnalysisInfo.h"

#include "EventReadFromFile.h"
#include "EventSim.h"

#include <iostream>
#include <sstream>

using namespace std;

SourceFactory::SourceFactory()
{
}

SourceFactory::~SourceFactory()
{
}

// create event source
EventSource *SourceFactory::create(const AnalysisInfo *info)
{
  // Check if "input" key is present in the AnalysisInfo object
  if (info->contains("input"))
  {
    // Create and return an instance of EventReadFromFile
    return new EventReadFromFile(info->value("input"));
  }
  // Check if "sim" key is present in the AnalysisInfo object
  if (info->contains("sim"))
  {
    stringstream sstr;
    // get number of events to generate
    sstr.str(info->value("sim"));
    unsigned int nevt;
    sstr >> nevt;
    // set seed if available
    unsigned int seed = 1;
    if (info->contains("seed"))
    {
      sstr.clear();
      sstr.str(info->value("seed"));
      sstr >> seed;
    }
    // Create and return an instance of EventSim
    return new EventSim(nevt, seed);
  }
  // Return nullptr if neither "input" nor "sim" keys are present
  return nullptr;
}
