#include "ProperTime.h"
#include "Event.h"
#include "Utilities.h"
#include "Constants.h"
#include "ParticleReco.h"
#include <iostream>
#include <cmath>

using namespace std;

// constructor
ProperTime::ProperTime()
{
}

// destructor
ProperTime::~ProperTime()
{
}

// recompute tag informations for new event
void ProperTime::update(const Event &ev)
{
  decayType = unknown;
  totalEnergy = -1.0;
  invariantMass = -1.0;
  static ParticleReco *ener = ParticleReco::instance();

  double x = ev.getX();
  double y = ev.getY();
  double z = ev.getZ();

  double d = sqrt(x * x + y * y + z * z);
  double e = ener->getParticleEnergy();
  double m = ener->getParticleMass();

  double p = sqrt(e * e - m * m);
  double c = Constants::lightVelocity;

  double t = (d * m) / (p * c);
  time = t;

  return;

  cout << "Update Proper time called: " << t << endl;
}

// return particle type
ProperTime::ParticleType ProperTime::getParticleType()
{
  // check for new event and return result
  check();
  return decayType;
}

// return particle energy
double ProperTime::getParticleEnergy()
{
  // check for new event and return result
  check();
  return totalEnergy;
}

// return particle mass
double ProperTime::getParticleMass()
{
  // check for new event and return result
  check();
  return invariantMass;
}

// return decay time
double ProperTime::getDecayTime()
{
  // check for new event and return result
  check();
  return time;
}
