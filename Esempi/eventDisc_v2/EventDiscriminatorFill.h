#ifndef EventDiscriminatorFill_h
#define EventDiscriminatorFill_h

#include "DiscriminatorFill.h"
#include "EventDiscriminator.h"

class Event;

class EventDiscriminatorFill: public DiscriminatorFill,
                              public EventDiscriminator {

 public:

  EventDiscriminatorFill();
  // deleted copy constructor and assignment to prevent unadvertent copy
  EventDiscriminatorFill           ( const EventDiscriminatorFill& x ) = delete;
  EventDiscriminatorFill& operator=( const EventDiscriminatorFill& x ) = delete;

  ~EventDiscriminatorFill() override;

  // create histograms
  void book();

  void fill( const Event& ev );

};

#endif

