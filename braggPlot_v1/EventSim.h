#ifndef EventSim_h
#define EventSim_h

#include "EventSource.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
class Event;

class EventSim: public EventSource {

 public:

  // simulate n events with random seed s
  EventSim( unsigned int n, unsigned int s );
  // deleted copy constructor and assignment to prevent unadvertent copy
  EventSim           ( const EventSim& x ) = delete;
  EventSim& operator=( const EventSim& x ) = delete;

  ~EventSim() override;

 private:

  // number of events to simulate
  int nMax;

  // last event identifier
  int evId;

  // get an event
  const Event* get() override;

  // generate and event
  const Event* generate();

  float pedestalMean;
  float pedestalRMS;
  struct ElementData {
    float evFrac;
    float eTotMean;
    float eTotRMS;
    std::vector<float> eMean;
    std::vector<float> eRMS;
  };
  std::vector<ElementData*> eData;

  ElementData* createElement( float evFrac,
                              float eTotMean,
                              float eTotRMS );

  // random number generation

  // uniform 
  static double randF() { return         random() *   1.0         /
                                                      RAND_MAX     ; }
  static double randF( float max ) {
                          return         random() *   max         /
                                                      RAND_MAX     ; }
  static double randF( float min, float max ) {
                          return min + ( random() * ( max - min ) /
                                                      RAND_MAX    ); }

  // phi angle
  static double randPhi() { return randF( 2.0 * M_PI ); }

  // exponential
  static double randE()  { return     -log( randF() ); }
  static double randE( float c )  {
                           return -c * log( randF() ); }

  // gaussian
  static double randG() { return                  sqrt( -log( randF() ) ) *
                                                         sin( randPhi() )    ; }
  static double randG( float sigma ) {
                          return          sigma * sqrt( -log( randF() ) ) *
                                                         sin( randPhi() )    ; }
  static double randG( float mean, float sigma ) {
                          return mean + ( sigma * sqrt( -log( randF() ) ) *
                                                         sin( randPhi() ) )  ; }

};

#endif

