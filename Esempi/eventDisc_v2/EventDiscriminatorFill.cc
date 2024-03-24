#include "EventDiscriminatorFill.h"
#include "Event.h"

EventDiscriminatorFill::EventDiscriminatorFill() {
}


EventDiscriminatorFill::~EventDiscriminatorFill() {
}


// create histograms
void EventDiscriminatorFill::book() {
  DiscriminatorFill::book( "chi2"    ,  4, 0.0, 40.0 );
  DiscriminatorFill::book( "muoKink" ,  7, 0.0, 70.0 );
  DiscriminatorFill::book( "trkKink" ,  4, 0.0, 20.0 );
  DiscriminatorFill::book( "deltaEta",  5, 0.0, 0.25 );
  DiscriminatorFill::book( "muoComp" ,  5, 0.0,  1.0 );
  DiscriminatorFill::book( "muoSum"  , 10, 0.0, 50.0 );
  return;
}


void EventDiscriminatorFill::fill( const Event& ev ) {
  compute( ev );
  DiscriminatorFill::fill( ev.evType() );
  return;
}

