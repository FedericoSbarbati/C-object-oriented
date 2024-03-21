#ifndef ElementReco_h
#define ElementReco_h

#include "AnalysisSteering.h"
#include <vector>

class Event;
class BraggMean;

class ElementReco: public AnalysisSteering {

 public:

  ElementReco();
  // deleted copy constructor and assignment to prevent unadvertent copy
  ElementReco           ( const ElementReco& x ) = delete;
  ElementReco& operator=( const ElementReco& x ) = delete;

  ~ElementReco() override;

  // function to be called at execution start
  void beginJob() override;
  // function to be called at execution end
  void   endJob() override;
  // function to be called for each event
  void process( const Event& ev ) override;

 private:

  // set of Bragg curves for different total energies
  std::vector<BraggMean*> bCurve;

};

#endif

