#include "EventDump.h"

#include "Event.h"
#include "AnalysisFactory.h"

#include <iostream>

using namespace std;

// DECLARATION AND DEFINITION OF EVENT DUMP FACTORY: concrete factory to create an EventDump analyzer (IMPORTANTE!!)
class EventDumpFactory : public AnalysisFactory::AbsFactory
{
public:
  // assign "dump" as name for this analyzer and factory (Calling base class constructor passing dump as info)
  EventDumpFactory() : AnalysisFactory::AbsFactory("dump") {}
  // create an EventDump when builder is run
  AnalysisSteering *create(const AnalysisInfo *info) override
  {
    return new EventDump(info); // Override of AbsFactory function for create that creates and return an Event Dump instance
  }
};

/*
Cronology of things happening:

1) DECLARATION of a static CONCRETE-FACTORY -> It's create before main() execution
2) CALL TO ABSFACTORY CONSTRUCTOR: It contains in the definition a call to the function registerFactory(string,AbsFactory);
2.1) registerFactory declares a static fm map that is allocated trough a call to the factoryMap() function
2.2) factoryMap() is  function that return a static map<string,AbsFactory*> type
2.3) registerFactory() insert the CONCRETE FACTORY into the resource returned by factoryMap()
3) The new derived type from Analysis steering can be created from the CONCRETE FACTORY now contained in factoryMap()
    that will exist for all the compilation time allowing the main to confront user input with the known factory.
4) After first instance of fm the static delcaration doesn't allow to be redefined so it's contents will be continously
  updated trough the creation and definition of ohter CONCRETE FARM
*/

// create a global EventDumpFactory, so that it is created and registered
// BEFORE main execution start:
// when the AnalysisFactory::create function is run,
// an EventDumpFactory will be available with name "dump".
static EventDumpFactory ed;

EventDump::EventDump(const AnalysisInfo *info) : AnalysisSteering(info)
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

  // write event number and number of points
  unsigned int n = ev.dataSize();
  cout << ev.eventNumber() << ' '
       << n;

  // write all points
  unsigned int i;
  for (i = 0; i < n; ++i)
    cout << ' ' << ev.energy(i);
  cout << endl;

  return;
}
