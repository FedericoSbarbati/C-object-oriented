#include <cmath>

#include "AnalysisObjects/MassMean.h"
#include "AnalysisFramework/Event.h"
#include "AnalysisObjects/ParticleReco.h"
#include "AnalysisUtilities/Constants.h"


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
  mean = massSum / ((double)nAccepted);
  rms = sqrt(squareSum / ((double)nAccepted) - mean * mean);

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
