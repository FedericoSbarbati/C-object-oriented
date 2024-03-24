#ifndef EventDiscriminatorRead_h
#define EventDiscriminatorRead_h

#include "DiscriminatorRead.h"
#include "EventDiscriminator.h"

class Event;

class EventDiscriminatorRead: public DiscriminatorRead,
                              public EventDiscriminator {

 public:

  EventDiscriminatorRead();
  // deleted copy constructor and assignment to prevent unadvertent copy
  EventDiscriminatorRead           ( const EventDiscriminatorRead& x ) = delete;
  EventDiscriminatorRead& operator=( const EventDiscriminatorRead& x ) = delete;

  ~EventDiscriminatorRead() override;

  // compute discriminating variable for an event
  float get( const Event& ev );

};

#endif

