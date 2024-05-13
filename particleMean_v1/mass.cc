#include <iostream>
#include <fstream>
#include <cmath>

#include "Event.h"

// compute energy from momentum x,y,z components and invariant mass
double energy(double px, double py, double pz, double mass)
{
  double en = sqrt(px * px + py * py + pz * pz + mass * mass);
  return en;
}

// compute invariant mass from momentum x,y,z components and energy
double invariantMass(double px, double py, double pz, double E)
{
  double invMsqrd = (E * E - (px * px + py * py + pz * pz));
  double invM = invMsqrd > 0 ? sqrt(invMsqrd) : -1;
  return invM;
}

double mass(const Event *ev)
{
  // Needed constants
  const double massPion = 0.1395706;   // GeV/c^2
  const double massProton = 0.938272;  // GeV/c^2
  const double massK0 = 0.497611;      // GeV/c^2
  const double massLambda0 = 1.115683; // GeV/c^2

  // retrieve particles in the event
  typedef const Particle *part_ptr;
  const part_ptr *particles = ev->part;

  // variables to loop over particles
  int n = ev->nParticle;

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
    part_ptr p = particles[i];

    // Updating momentum sums
    pxTot += p->px;
    pyTot += p->py;
    pzTot += p->pz;

    // Updating energy sums:
    // 1-K0 hypotheses (pion mass for both particle)
    double Ek = energy(p->px, p->py, p->pz, massPion);
    EtotKO += Ek;
    // 2-L0 hypotheses
    double EL;
    if (p->charge > 0)
    {
      EL = energy(p->px, p->py, p->pz, massProton);
      posN++;
    }
    else
    {
      EL = energy(p->px, p->py, p->pz, massPion);
      negN++;
    }
    EtotLO += EL;
  }
  if (!(negN == 1 && posN == 1))
  {
    return -1;
  }

  // invariant masses for different decay product mass hypotheses
  double invMassKO = invariantMass(pxTot, pyTot, pzTot, EtotKO);
  double invMassLO = invariantMass(pxTot, pyTot, pzTot, EtotLO);

  // compare invariant masses with known values and return the nearest one
  double prec1 = std::abs(invMassKO - massK0);
  double prec2 = std::abs(invMassLO - massLambda0);

  if (prec1 > prec2)
  {
    return invMassLO;
  }
  else
  {
    return invMassKO;
  }
}
