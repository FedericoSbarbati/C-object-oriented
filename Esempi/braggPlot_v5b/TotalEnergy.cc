#include "TotalEnergy.h"
#include "Event.h"
#include "Constants.h"

#include <iostream>
using namespace std;


TotalEnergy::TotalEnergy() {
}


TotalEnergy::~TotalEnergy() {
}


// function to be called when a new event arrives
void TotalEnergy::update( const Event& ev ) {
  // set sum at 0
  dataSum = bkgsSum = 0.0;
  // loop over points
  int e;
  int i;
  int n = Event::minSize;
  for ( i = 0; i < n; ++i ) {
    // get energy measurement
    e = ev.energy( i );
    // update sum
    dataSum += e;
    bkgsSum += e - Constants::bgMean;
  }
  return;
}


// sum of measurements, no background subtraction
float TotalEnergy::rawSum() {
  // check for new event and return result
  check();
  return dataSum;
}


// total energy, background subtracted
float TotalEnergy::energy() {
  // check for new event and return result
  check();
  return bkgsSum;
}

