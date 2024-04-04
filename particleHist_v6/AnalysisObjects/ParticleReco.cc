#include "AnalysisObjects/ParticleReco.h"
#include "AnalysisFramework/Event.h"
#include "AnalysisUtilities/Utilities.h"
#include "AnalysisUtilities/Constants.h"
#include <iostream>
#include <cmath>

using namespace std;

// constructor
ParticleReco::ParticleReco()
{
}

// destructor
ParticleReco::~ParticleReco()
{
}

// recompute tag informations for new event
void ParticleReco::update(const Event &ev)
{

  // set default quantities for an undefined event (not physical)
  decayType = unknown;
  totalEnergy = -1.0;
  invariantMass = -1.0;

  // variables to loop over particles
  int n = ev.getnParticle();

  // positive / negative track counters
  int negN = 0;
  int posN = 0;

  // variables for momentum sums
  double pxTot = 0;
  double pyTot = 0;
  double pzTot = 0;

  // variables for energy sums, for K0 and Lambda0
  double EtotKO = 0;
  double EtotLO = 0;

  for (int i = 0; i < n; i++)
  {
    Event::part_ptr p = ev.particle(i);
    // Updating momentum sums
    pxTot += p->px;
    pyTot += p->py;
    pzTot += p->pz;

    // Updating energy sums:
    // 1-K0 hypotheses (pion mass for both particle)
    double Ek = Utilities::energy(p->px, p->py, p->pz, Constants::massPion);
    EtotKO += Ek;
    // 2-L0 hypotheses
    double EL;
    if (p->charge > 0)
    {
      EL = Utilities::energy(p->px, p->py, p->pz, Constants::massProton);
      posN++;
    }
    else
    {
      EL = Utilities::energy(p->px, p->py, p->pz, Constants::massPion);
      negN++;
    }
    EtotLO += EL;
  }
  if (!(negN == 1 && posN == 1))
  {
    return; // Non updated private member-> Error handling
  }

  // code to compute total energy and invariant mass for the two
  // mass hypotheses for the decay products

  double invMassKO = Utilities::invariantMass(pxTot, pyTot, pzTot, EtotKO);
  double invMassLO = Utilities::invariantMass(pxTot, pyTot, pzTot, EtotLO);

  // compare invariant masses with known values and set final values
  // ( type, energy and mass )
  double prec1 = std::abs(invMassKO - Constants::massK0);
  double prec2 = std::abs(invMassLO - Constants::massLambda0);

  if (prec1 > prec2)
  {
    decayType = Lambda0;
    invariantMass = invMassLO;
    totalEnergy = EtotLO;
    return;
  }
  else
  {
    decayType = K0;
    invariantMass = invMassKO;
    totalEnergy = EtotKO;
    return;
  }

}

// return particle type
  ParticleReco::ParticleType ParticleReco::getParticleType() 
  {
    // check for new event and return result
    check();
    return decayType;

    }

// return particle energy
double ParticleReco::getParticleEnergy() 
{
    // check for new event and return result
    check();
    return totalEnergy;
    }

// return particle mass
double ParticleReco::getParticleMass() 
{
  // check for new event and return result
  check();
  return invariantMass;
}
