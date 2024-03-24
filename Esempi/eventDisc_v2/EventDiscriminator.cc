#include "EventDiscriminator.h"
#include "Event.h"

#include <cmath>

//#define regVar(NAME) registerVariable( #NAME, &NAME )

EventDiscriminator::EventDiscriminator() {
  // pass all quantities to the generic discriminator
  registerVariable( "chi2"    , &chi2     );
  registerVariable( "muoKink" , &muoKink  );
  registerVariable( "trkKink" , &trkKink  );
  registerVariable( "deltaEta", &deltaEta );
  registerVariable( "muoComp" , &muoComp  );
  registerVariable( "muoSum"  , &muoSum   );
/*
  regVar( chi2     );
  regVar( muoKink  );
  regVar( trkKink  );
  regVar( deltaEta );
  regVar( muoComp  );
  regVar( muoSum   );
*/
}


EventDiscriminator::~EventDiscriminator() {
}


// compute event variables
void EventDiscriminator::compute( const Event& ev ) {
  float x  = ev.muoX();
  float y  = ev.muoY();
  float a  = ev.muoA();
  float b  = ev.muoB();
  chi2     = sqrt( x * y );
  muoKink  = sqrt( x / y );
  if ( muoKink > 60.0 ) muoKink = ( muoKink / 4.0 ) + 45.0;
  trkKink  = log( ev.trkKink() );
  if ( trkKink > 15.0 ) trkKink = ( trkKink / 3.0 ) + 10.0;
  deltaEta = ev.muoEta2() - ev.muoEta1();
  muoComp  = ( a + b ) / 2.0;
  muoSum   = ( a - b ) / 2.0;
  if ( muoSum > 42.0 ) muoSum = ( muoSum / 6.0 ) + 35.0;
  return;
}

