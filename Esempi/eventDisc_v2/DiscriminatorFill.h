#ifndef DiscriminatorFill_h
#define DiscriminatorFill_h

#include "DiscriminatorBase.h"
#include "DiscriminatorClassification.h"

#include <string>

class TH1F;

class DiscriminatorFill: public virtual DiscriminatorBase {

 public:

  DiscriminatorFill();
  // deleted copy constructor and assignment to prevent unadvertent copy
  DiscriminatorFill           ( const DiscriminatorFill& x ) = delete;
  DiscriminatorFill& operator=( const DiscriminatorFill& x ) = delete;

  ~DiscriminatorFill() override;

  // create histograms for a specific quantity
  void book( const std::string& name, int nb, float xmin, float xmax );

  // fill histograms for "signal" or "background" events
  void fill( DiscriminatorClassification::Type type );
  // save histograms for "signal" or "background" events
  void save( const std::string& name );

 private:

  // fill histograms for a specific quantity
  void fill( DiscriminatorBase::VarDescription* vd,
             DiscriminatorClassification::Type type );
  // normalize histogram to have s=1 with s=sum of bin content
  void normalizeHisto( TH1F* h );

};

#endif

