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
  static ParticleReco *ener = ParticleReco::instance();

  // Setting private members from previous analysis
  decayType = unknown; //Check
  totalEnergy = ener->getParticleEnergy();
  invariantMass = ener->getParticleMass();

  double d = sqrt(ev.getX() * ev.getX() + ev.getY() * ev.getY() + ev.getZ() * ev.getZ());
  double p = sqrt(totalEnergy * totalEnergy - invariantMass * invariantMass); //Momentum

  double t = (d*invariantMass)/(p*Constants::lightVelocity);
  time = t;
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
