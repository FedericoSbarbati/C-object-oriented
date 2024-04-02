#include <cmath>

#include "LifetimeFit.h"
#include "Event.h"
#include "ParticleReco.h"
#include "Constants.h"

using namespace std;

// constructor
LifetimeFit::LifetimeFit(float min, float max) : minMass(min),
                                                 maxMass(max)
// initializations
{
  nAccepted = 0;
}

// destructor
LifetimeFit::~LifetimeFit()
{
}

// add data from a new event
bool LifetimeFit::add(const Event &ev)
{
  static ParticleReco *ener = ParticleReco::instance();
  double invMass = ener->getParticleMass();

  cout << "Lifetimefit::Add -Inv mass: " << invMass;
  // Check masses range
  if (invMass >= minMass && invMass <= maxMass)
  {
    cout << " - Risultato true" << endl;
    nAccepted++;
    return true;
  }
  else
  {
        cout << " - Risultato false" << endl;
    return false;
  }
}

void LifetimeFit::compute()
{
  return;
}

int LifetimeFit::getNacceptedEv() const
{
  return nAccepted;
}
