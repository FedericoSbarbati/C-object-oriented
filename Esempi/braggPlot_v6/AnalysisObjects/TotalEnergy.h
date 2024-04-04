#ifndef TotalEnergy_h
#define TotalEnergy_h

#include "util/include/Singleton.h"
#include "util/include/LazyObserver.h"
class Event;

class TotalEnergy: public Singleton<TotalEnergy>,
                   public LazyObserver<Event> {

  friend class Singleton<TotalEnergy>;

 public:

  // function to be called when a new event arrives
  void update( const Event& ev ) override;

  // sum of measurements, no background subtraction
  float rawSum();
  // total energy, background subtracted
  float energy();

 private:

  // private constructor and destructor for singleton
  TotalEnergy();
  // deleted copy constructor and assignment to prevent unadvertent copy
  TotalEnergy           ( const TotalEnergy& x ) = delete;
  TotalEnergy& operator=( const TotalEnergy& x ) = delete;

  ~TotalEnergy() override;

  // sum of data, no background subtraction
  float dataSum;
  // sum of energies, background subtracted
  float bkgsSum;

};

#endif

