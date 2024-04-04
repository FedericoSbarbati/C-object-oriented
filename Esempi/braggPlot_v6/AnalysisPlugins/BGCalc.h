#ifndef BGCalc_h
#define BGCalc_h

#include "util/include/ActiveObserver.h"
#include "AnalysisFramework/AnalysisSteering.h"

class AnalysisInfo;
class Event;

class BGCalc: public AnalysisSteering,
              public ActiveObserver<Event> {

 public:

  BGCalc( const AnalysisInfo* info );
  // deleted copy constructor and assignment to prevent unadvertent copy
  BGCalc           ( const BGCalc& x ) = delete;
  BGCalc& operator=( const BGCalc& x ) = delete;

  ~BGCalc() override;

  // function to be called at execution start
  void beginJob() override;
  // function to be called at execution end
  void   endJob() override;
  // function to be called for each event
  void update( const Event& ev ) override;

 private:

  // min and max energy, min and max point
  int eMin;
  int eMax;
  int bMin;
  int bMax;

  // number of selected events, sum of energies and sum of square energies
  int nEvt;
  float bSum;
  float bSqr;

};

#endif

