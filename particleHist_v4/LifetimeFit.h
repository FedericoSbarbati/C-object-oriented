#ifndef LifetimeFit_h
#define LifetimeFit_h

class Event;
class ParticleReco;

class LifetimeFit
{

public:
  // constructor
  LifetimeFit(float min, float max); // mass range

  // destructor
  ~LifetimeFit();

  bool add(const Event &ev); // add data from a new event
  void compute();            

  int getNacceptedEv() const; // return number of accepted events

private:
  double minMass; // min mass
  double maxMass; // max mass

  int nAccepted;    // number of accepted events
};

#endif
