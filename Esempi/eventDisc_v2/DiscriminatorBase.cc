#include "DiscriminatorBase.h"

#include "TH1F.h"
#include "TFile.h"

using namespace std;

DiscriminatorBase::DiscriminatorBase() {
}


DiscriminatorBase::~DiscriminatorBase() {
}


// access quantity information map

map<string,DiscriminatorBase::VarDescription*>::const_iterator
           DiscriminatorBase::begin() {
  return varMap.begin();
}


map<string,DiscriminatorBase::VarDescription*>::const_iterator
           DiscriminatorBase::find( const string& name ) {
  return varMap.find( name );
}


map<string,DiscriminatorBase::VarDescription*>::const_iterator
                     DiscriminatorBase::end() {
  return varMap.end();
}


// compute discriminating variable for the full set of quantities
float DiscriminatorBase::get() const {
  // initialize probabilities
  float dSig = 0.5;
  // loop over quantities
  for ( const auto& element: varMap ) {
    VarDescription* vd = element.second;
    // skip unused quantities
    if ( !vd->use ) continue;
    // update probabilities for each variable
    get( *vd->content, dSig, vd->sigHisto, vd->bkgHisto );
  }
  // return discriminating variable
  return dSig;
}


// accept variables from derived classes
void DiscriminatorBase::registerVariable( const string& name,
                                          const float* content, bool active ) {
  // create a new information set
  VarDescription* vd = new VarDescription;
  // store informations
  vd->content  = content;
  vd->bkgHisto =
  vd->sigHisto = nullptr;
  vd->use      = active;
  // insert set into map
  varMap[name] = vd;
  return;  
}


// activate or deactivate use of a specific quantity
void DiscriminatorBase::setVariable( const string& name, bool active ) {
  // find information set for this quantity
  map<string,VarDescription*>::const_iterator iter = find( name );
  map<string,VarDescription*>::const_iterator iend = end();
  if ( iter == iend ) return;
  // set active status
  iter->second->use = active;
  return;
}


// compute probabilities for a variable
void DiscriminatorBase::get( float x, float& dSig,
                             TH1F* hSig, TH1F* hBkg ) {
  float dBkg = 1.0 - dSig;
  // get probabilities for signal and background
  float bkg = hBkg->GetBinContent( hBkg->FindBin( x ) );
  float sig = hSig->GetBinContent( hSig->FindBin( x ) );
  // skip zeros
  if ( sig < 1.0e-06 ) return;
  if ( bkg < 1.0e-06 ) return;
  // update probabilities
  dSig *= sig;
  dBkg *= bkg;
  // normalize probabilities
  float
  dSum = dBkg + dSig;
  dSig /= dSum;
  return;
}

