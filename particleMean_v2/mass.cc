#include <cmath>

#include "Event.h"
#include "Utilities.h"
#include "Constants.h"


double mass(const Event &ev)
{
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
    return -1;
  }

  // invariant masses for different decay product mass hypotheses
  double invMassKO = Utilities::invariantMass(pxTot, pyTot, pzTot, EtotKO);
  double invMassLO = Utilities::invariantMass(pxTot, pyTot, pzTot, EtotLO);

  // compare invariant masses with known values and return the nearest one
  double prec1 = std::abs(invMassKO - Constants::massK0);
  double prec2 = std::abs(invMassLO - Constants::massLambda0);

  if (prec1 > prec2)
  {
    return invMassLO;
  }
  else
  {
    return invMassKO;
  }

}
