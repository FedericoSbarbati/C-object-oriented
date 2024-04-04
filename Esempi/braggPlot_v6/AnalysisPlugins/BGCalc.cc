#include "AnalysisPlugins/BGCalc.h"

#include "AnalysisFramework/Event.h"
#include "AnalysisFramework/AnalysisInfo.h"
#include "AnalysisFramework/AnalysisFactory.h"
#include "AnalysisObjects/TotalEnergy.h"

#include <iostream>
#include <cmath>

using namespace std;

// define a builder for this analyzer and register it
class BGCalcFactory: public AnalysisFactory::AbsFactory {
 public:
  BGCalcFactory(): AnalysisFactory::AbsFactory( "bg" ) {}
  AnalysisSteering* create( const AnalysisInfo* info ) override {
    return new BGCalc( info );
  }
};
// create a global BGCalcFactory, so that it is created and registered 
// before main execution start:
// when the AnalysisFactory::create function is run,
// a BGCalcFactory will be available with name "bg".
static BGCalcFactory bg;

BGCalc::BGCalc( const AnalysisInfo* info ):
 AnalysisSteering( info ) {
}


BGCalc::~BGCalc() {
}


void BGCalc::beginJob() {

  // min and max energy, min and max point
  eMin = 3000;
  eMax = 5000;
  bMin = 100;
  bMax = 120;

  // number of selected events, sum of energies and sum of square energies
  nEvt = bSum = bSqr = 0;

  return;

}


void BGCalc::update( const Event& ev ) {

  // total energy
  static TotalEnergy* eTot = TotalEnergy::instance();
  float eRaw = eTot->rawSum();
  if ( eRaw < eMin ) return;
  if ( eRaw > eMax ) return;

  // loop over points and update sums
  int iBin;
  for ( iBin = bMin; iBin < bMax; ++iBin ) {
    int ene = ev.energy( iBin );
    bSum +=   ene;
    bSqr += ( ene * ene );
  }

  // update event counter
  ++nEvt;

  return;

}


void BGCalc::endJob() {

  // compute background

  // number of points
  int nBin = bMax - bMin;
  // total number of measurements
  int nTot = nEvt * nBin;
  // compute mean and rms
  float bMean =          bSum * 1.0 / nTot;
  float bRMS  = sqrt ( ( bSqr * 1.0 / nTot ) - ( bMean * bMean ) );
  // printout result
  cout << nEvt << endl;
  cout << "background " << bMean << " +- " << bRMS << endl;

  return;

}

