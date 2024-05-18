#include <cmath>
#include <iostream>

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
void MassMean::add(const Event &ev)
{
  double invMass = mass(ev);
  // Check if the invariant mass is within the specified range
  if (invMass >= minMass && invMass <= maxMass)
  {
    invMass -= minMass; // Subtracting min mass
    massSum += invMass;
    squareSum += (invMass * invMass);
    nAccepted++;
  }
}

// Compute the mean and rms of the accepted events
void MassMean::compute()
{

  // Check for call with no data
  if (nAccepted == 0)
  {
    std::cout << "No accepted events" << std::endl;
    return;
  }
  mean = massSum / ((double)nAccepted);
  rms = sqrt(squareSum / ((double)nAccepted) - mean * mean);

  mean += minMass; // Re-adding min mass
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

// Get the RMS of the accepted events
double MassMean::getRMS() const
{
  return rms;
}
