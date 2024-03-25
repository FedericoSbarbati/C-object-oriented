#ifndef ElementReco_h
#define ElementReco_h

#include "util/include/ActiveObserver.h"
#include "AnalysisSteering.h"
#include <string>
#include <vector>

class AnalysisInfo;
class Event;
class BraggMean;
class TH1F;

class ElementReco: public AnalysisSteering,
                   public ActiveObserver<Event> {

 public:

  ElementReco( const AnalysisInfo* info );
  // deleted copy constructor and assignment to prevent unadvertent copy
  ElementReco           ( const ElementReco& x ) = delete;
  ElementReco& operator=( const ElementReco& x ) = delete;

  ~ElementReco() override;

  // function to be called at execution start
  void beginJob() override;
  // function to be called at execution end
  void   endJob() override;
  // function to be called for each event
  void update( const Event& ev ) override;

 private:

  // Bragg curve information
  struct BraggCurve {
    std::string name;  // element name
    BraggMean*  bMean; // statistic object
    TH1F*       hMean; // graph
  };

  // set of Bragg curves for different total energies
  std::vector<BraggCurve*> bCurve;

  // create objects for a Bragg curve
  void bCreate( const std::string& name, float min, float max );

};

#endif

