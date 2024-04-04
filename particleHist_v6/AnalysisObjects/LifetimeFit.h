#ifndef LifetimeFit_h
#define LifetimeFit_h

#include <vector>

class Event;
class ParticleReco;

class LifetimeFit
{

public:
  // constructor
  LifetimeFit(double minMass, double maxMass, double minTime, double maxTime, double minScan, double maxScan, double scanStep);
  // destructor
  ~LifetimeFit();

  bool add(const Event &ev); // add data from a new event
  void compute();

  int getNacceptedEv() const; // return number of accepted events

  double getLifeTime() const;      // return mean lifetime
  double getLifeTimeError() const; // return lifetime error

private:
  double minMass; 
  double maxMass; // Mass range

  double minTime;
  double maxTime; // Time range

  double minScan;
  double maxScan;  // Step range
  double scanStep; // scan step

  std::vector<double> decayTimes;

  double ltMean;
  double ltRMS;
};

#endif
