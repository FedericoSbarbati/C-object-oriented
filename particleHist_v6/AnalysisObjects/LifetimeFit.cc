#include <cmath>

#include "AnalysisUtilities/QuadraticFitter.h"
#include "AnalysisObjects/LifetimeFit.h"
#include "AnalysisFramework/Event.h"
#include "AnalysisObjects/ProperTime.h"
#include "AnalysisObjects/ParticleReco.h"
#include "AnalysisUtilities/Constants.h"

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
bool LifetimeFit::add(const Event &ev)
{
  static ParticleReco *pr = ParticleReco::instance();
  static ProperTime *pt = ProperTime::instance();
  double m = pr->getParticleMass();
  double dt = pt->getDecayTime();

  if (m >= minMass && m <= maxMass)
  {
    if (dt >= minTime && dt <= maxTime)
    {
      decayTimes.push_back(dt);
      return true;
    }
  }
  return false;
}

// Get methods implementation of the class
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

// Calcolate the mean and the RMS of the decay times
void LifetimeFit::compute()
{
  // Create an instance of QuadraticFitter
  QuadraticFitter fitter;

  // Loop over the scan range
  for (double t_s = minScan; t_s < maxScan; t_s += scanStep)
  {
    // Initialize the likelihood (L) to zero
    double L = 0.0;
    double t_i = 0.0;

    // Loop over all decay times
    for (unsigned int i = 0; i < decayTimes.size(); i++)
    {
      // Get the i-th decay time
      t_i = decayTimes[i];

      // Update the likelihood based on the current decay time and scan value
      L += (t_i / t_s) + log(t_s) + log(exp(-minTime / t_s) - exp(-maxTime / t_s));
    }

    // Add the scan value and likelihood to the fitter
    fitter.add(t_s, L);
  }

  // Get the coefficients of the fitted quadratic function
  //double a = fitter.a();
  double b = fitter.b();
  double c = fitter.c();

  // Calculate the mean lifetime (t) and its error
  ltMean = -b / (2. * c);
  ltRMS = c > 0.0 ? 1.0 / sqrt(2.0 * c) : 0.0;

  return;
}
