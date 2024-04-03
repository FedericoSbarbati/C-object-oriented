#include "EventDump.h"

#include "Event.h"
#include "AnalysisFactory.h"
#include "util/include/Output.h"

#include <iostream>

using namespace std;

// concrete factory to create an EventDump analyzer
class EventDumpFactory: public AnalysisFactory::AbsFactory {
 public:
  // assign "dump" as name for this analyzer and factory
  EventDumpFactory(): AnalysisFactory::AbsFactory( "dump" ) {}
  // create an EventDump when builder is run
  AnalysisSteering* create( const AnalysisInfo* info ) override {
    return new EventDump( info );
  }
};
// create a global EventDumpFactory, so that it is created and registered 
// before main execution start:
// when the AnalysisFactory::create function is run,
// an EventDumpFactory will be available with name "dump".
static EventDumpFactory ed;

EventDump::EventDump( const AnalysisInfo* info ):
 AnalysisSteering( info ) {
}


EventDump::~EventDump() {
}


// function to be called at execution start
void EventDump::beginJob() {
  char m = *aInfo->value( "omode" ).c_str();
  if ( m == 'B' ) m = 'b';
  out = OutputFactory::create( aInfo->value( "ofile" ),
                               m == 'b' ? std::ios::binary : std::ios::out );
  return;
}


// function to be called at execution end
void EventDump::endJob() {
  delete out;
  return;
}


// function to be called for each event
void EventDump::update( const Event& ev ) {

  // write event number and number of points
  unsigned int n = ev.dataSize();
  *out << ev.eventNumber() << Output::Cleaner( ' ' )
       << n;

  // write all points
  unsigned int i;
  for ( i = 0; i < n; ++i ) *out << Output::Cleaner( ' ' ) << ev.energy( i );
  *out << Output::Cleaner( std::endl );

  return;

}

