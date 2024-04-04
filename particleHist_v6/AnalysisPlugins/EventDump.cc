#include <iostream>

#include "AnalysisPlugins/EventDump.h"
#include "AnalysisFramework/Event.h"
#include "AnalysisFramework/AnalysisFactory.h"


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
void EventDump::update(const Event &ev)
{
  cout << ev.getnParticle() << endl;
  cout << ev.getX() << ' ' << ev.getY() << ' ' << ev.getZ() << endl;

  for (int i = 0; i < ev.getnParticle(); i++)
  {
    Event::part_ptr p = ev.particle(i);
    cout << ' ' << p->charge << ' '
         << p->px << ' ' << p->py << ' ' << p->pz << endl;
  }

  return;
}
