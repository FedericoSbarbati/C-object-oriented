#include "ElementReco.h"

#include "Event.h"
#include "BraggMean.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

ElementReco::ElementReco() {
}


ElementReco::~ElementReco() {
}


// function to be called at execution start
void ElementReco::beginJob() {

  // create energy distributions for different total energy ranges
  bCurve.reserve( 10 );
  // background
  bCurve.push_back( new BraggMean( 3000.0, 5000.0 ) );
  // amaronium
  bCurve.push_back( new BraggMean( 6000.0, 6499.0 ) );
  // barberium
  bCurve.push_back( new BraggMean( 6500.0, 6799.0 ) );
  // cabernetium
  bCurve.push_back( new BraggMean( 6800.0, 7200.0 ) );

  return;

}


// function to be called at execution end
void ElementReco::endJob() {

  // number of points
  int nBinD = Event::minSize;
  int iBinD;

  // loop over elements
  for ( BraggMean* bMean: bCurve ) {
    // get mean and rms energies
    const vector<double>& mean = bMean->eMean(); // Qua ha effetto la Lazy Evaluation: se non li chiedi non li chiama
    const vector<double>& rms  = bMean->eRMS ();
    // loop over points
    for ( iBinD = 0; iBinD < nBinD; ++iBinD ) {
      // print results
      cout << iBinD << " " << mean[iBinD] << " " << rms[iBinD] << endl;
    }
    // print number of events
    cout << bMean->nEvents() << endl;
  }

  return;

}


// function to be called for each event
void ElementReco::process( const Event& ev ) {
  // loop over energy distributions and pass event to each of them
  for ( BraggMean* bMean: bCurve ) bMean->add( ev );
  return;
}

