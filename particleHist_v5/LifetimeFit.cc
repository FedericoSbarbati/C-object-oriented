#include <cmath>

#include "QuadraticFitter.h"
#include "LifetimeFit.h"
#include "Event.h"
#include "ProperTime.h"
#include "Constants.h"

using namespace std;

// constructor
LifetimeFit::LifetimeFit(double minMass, double maxMass, double minTime, double maxTime,
                         double minScan, double maxScan, double scanStep) : minMass(minMass),
                                                                            maxMass(maxMass),
                                                                            minTime(minTime),
                                                                            maxTime(maxTime),
                                                                            minScan(minScan),
                                                                            maxScan(maxScan),
                                                                            scanStep(scanStep)
{
}

// destructor
LifetimeFit::~LifetimeFit()
{
}

// add data from a new event
/*
- in the "add" function get the decay time from "ProperTime" and,
  if it's inside the [min,max] range, save it in the std::vector of all the
  decay times,
*/
bool LifetimeFit::add(const Event &ev)
{
  static ProperTime *pt = ProperTime::instance();
  double decayTime = pt->getDecayTime();
  if (decayTime >= minTime && decayTime <= maxTime)
  {
    decayTimes.push_back(decayTime);
    return true;
  }
  else
    return;
}

// Calcolate the mean and the RMS of the decay times
void LifetimeFit::compute()
{
  // Create an instance of QuadraticFitter
  QuadraticFitter fitter;

  // Define the minimum, maximum, and step size for the scan
  double t_min = minScan;
  double t_max = maxScan;
  double t_step = scanStep;

  // Loop over the scan range
  for (double t_s = t_min; t_s <= t_max; t_s += t_step)
  {
    // Initialize the likelihood (L) to zero
    double L = 0.0;

    // Loop over all decay times
    for (int i = 0; i < decayTimes.size(); i++)
    {
      // Get the i-th decay time
      double t_i = decayTimes[i];

      // Update the likelihood based on the current decay time and scan value
      L += (t_i / t_s) + log(t_s) + log(exp(-t_min / t_s) - exp(-t_max / t_s));
    }

    // Add the scan value and likelihood to the fitter
    fitter.add(t_s, L);
  }

  // Get the coefficients of the fitted quadratic function
  double a = fitter.a();
  double b = fitter.b();
  double c = fitter.c();

  // Calculate the mean lifetime (t) and its error
  double t = -b / (2 * c);
  double error = 1 / sqrt(2 * c);

  // Store the mean lifetime and its error
  ltMean = t;
  ltRMS = error;

  return;
}

// Get methods of the class
int LifetimeFit::getNacceptedEv() const
{
  return decayTimes.size();
}
double LifetimeFit::getLifeTime() const
{
  return ltMean;
}
double LifetimeFit::getLifeTimeError() const
{
  return ltRMS;
}
