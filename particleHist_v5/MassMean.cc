#include <cmath>

#include "MassMean.h"
#include "Event.h"
#include "ParticleReco.h"
#include "Constants.h"

// constructor
MassMean::MassMean(float min, float max) : minMass(min),
                                           maxMass(max)
// initializations
{
  nAccepted = 0;
  massSum = 0;
  squareSum = 0;
}

// destructor
MassMean::~MassMean()
{
}

// add data from a new event
bool MassMean::add(const Event &ev)
{
  static ParticleReco *ener = ParticleReco::instance();
  double invMass = ener->getParticleMass();
  // Check masses range
  if (invMass >= minMass && invMass <= maxMass)
  {
    invMass -= minMass; // Subtracting min
    massSum += invMass;
    squareSum += (invMass * invMass);
    nAccepted++;

    return true;
  }
  else
    return false;
}

// compute mean and rms
void MassMean::compute()
{
  // Check for call with no data
  if (nAccepted == 0)
  {
    std::cout << "No accepted events" << std::endl;
    return;
  }

  mean = massSum / static_cast<double>(nAccepted);
  rms = sqrt(squareSum / static_cast<double>(nAccepted) - mean * mean);

  mean += minMass; // Re-adding min
}

int MassMean::getNacceptedEv() const
{
  return nAccepted;
}

double MassMean::getMean() const
{
  return mean;
}

double MassMean::getRMS() const
{
  return rms;
}
