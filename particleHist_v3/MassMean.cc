#include <cmath>

#include "MassMean.h"
#include "Event.h"
#include "Constants.h"

// Function to calculate the invariant mass of an event
double mass(const Event &ev);

// Constructor
MassMean::MassMean(float min, float max) : minMass(min),
                                           maxMass(max)
// Initializations
{
  nAccepted = 0;
  massSum = 0;
  squareSum = 0;
}

// Destructor
MassMean::~MassMean()
{
}

// Add data from a new event
bool MassMean::add(const Event &ev)
{
  double invMass = mass(ev);
  // Check if the invariant mass is within the specified range
  if (invMass >= minMass && invMass <= maxMass)
  {
    invMass -= minMass; // Subtracting minMass to normalize the range
    massSum += invMass;
    squareSum += (invMass * invMass);
    nAccepted++;

    return true;
  }
  else
    return false;
}

// Compute the mean and rms of the accepted events
void MassMean::compute()
{
  mean = massSum / ((double)nAccepted);
  rms = sqrt(squareSum / ((double)nAccepted) - mean * mean);

  mean += minMass; // Re-adding minMass to obtain the actual mean
}

// Get the number of accepted events
int MassMean::getNacceptedEv() const
{
  return nAccepted;
}

// Get the mean of the accepted events
double MassMean::getMean() const
{
  return mean;
}

// Get the rms of the accepted events
double MassMean::getRMS() const
{
  return rms;
}
