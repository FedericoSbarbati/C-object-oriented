#include "EventDiscriminatorRead.h"

EventDiscriminatorRead::EventDiscriminatorRead() {
}


EventDiscriminatorRead::~EventDiscriminatorRead() {
}


// compute discriminating variable for an event
float EventDiscriminatorRead::get( const Event& ev ) {
  // compute event variables
  compute( ev );
  // forward call to generic discriminator
  return DiscriminatorRead::get();
}

