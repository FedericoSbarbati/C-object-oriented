#include <cmath>

#include "MassMean.h"
#include "Event.h"
#include "Constants.h"

double mass(const Event &ev);

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
void MassMean::add(const Event &ev)
{
  double invMass = mass(ev);
  // Check masses range
  if (invMass >= minMass && invMass <= maxMass)
  {
    invMass -= minMass; // Subtracting min
    massSum += invMass;
    squareSum += (invMass * invMass);
    nAccepted++;
  }

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
