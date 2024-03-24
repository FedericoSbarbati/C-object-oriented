#ifndef EventDiscriminator_h
#define EventDiscriminator_h

#include "DiscriminatorBase.h"

class Event;

class EventDiscriminator: public virtual DiscriminatorBase {

 public:

  EventDiscriminator();
  // deleted copy constructor and assignment to prevent unadvertent copy
  EventDiscriminator           ( const EventDiscriminator& x ) = delete;
  EventDiscriminator& operator=( const EventDiscriminator& x ) = delete;

  ~EventDiscriminator() override;

  // compute event variables
  void compute( const Event& ev );

 private:

  // event variables
  float chi2    ;
  float muoKink ;
  float trkKink ;
  float deltaEta;
  float muoComp ;
  float muoSum  ;

};

#endif

