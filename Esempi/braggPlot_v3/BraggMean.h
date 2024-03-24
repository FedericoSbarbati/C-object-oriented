#ifndef BraggMean_h
#define BraggMean_h

#include <vector>

class Event;

class BraggMean {

 public:

  // create a set of counters for events with 
  // total energy between minEnergy and maxEnergy
  BraggMean( int minEnergy, int maxEnergy );
  // deleted copy constructor and assignment to prevent unadvertent copy
  BraggMean           ( const BraggMean& x ) = delete;
  BraggMean& operator=( const BraggMean& x ) = delete;

  ~BraggMean();

  // add an event, after checking for total energy
  void add( const Event& ev );
  // compute mean and rms
  void compute();

  // return results:
  // number of events with total energy in the range
  // array of mean energies for each point
  // array of rms  energies for each point
  int nEvents() const { return nEvt; }
  const std::vector<double>& eMean() const;
  const std::vector<double>& eRMS()  const;

 private:

  // min and max energy, number of selected events
  int eMin;
  int eMax;
  int nEvt;

  // arrays with sum of energies and sum of square energies
  std::vector<double> sum;
  std::vector<double> sqr;

  // arrays with mean and rms energies
  std::vector<double> mean;
  std::vector<double> rms;

};

#endif

