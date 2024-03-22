#ifndef MassMean_h
#define MassMean_h

class Event;

class MassMean
{

public:
  // constructor
  MassMean(float min, float max); // mass range

  // destructor
  ~MassMean();

  bool add(const Event &ev); // add data from a new event
  void compute();            // compute mean and rms

  int getNacceptedEv() const; // return number of accepted events
  double getMean() const;     // return mean mass
  double getRMS() const;      // return rms  mass

private:
  double minMass; // min mass
  double maxMass; // max mass

  int nAccepted;    // number of accepted events
  double massSum;   // sum of masses
  double squareSum; // sum of masses square

  double mean; // mean mass
  double rms;  // rms  mass
};

#endif
