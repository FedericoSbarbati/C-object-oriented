#include "DiscriminatorFill.h"

#include "TH1F.h"
#include "TFile.h"

using namespace std;

DiscriminatorFill::DiscriminatorFill() {
}


DiscriminatorFill::~DiscriminatorFill() {
}


// create histograms for a specific quantity
void DiscriminatorFill::book( const string& name,
                              int nb, float xmin, float xmax ) {
  // find information set for this quantity
  map<string,VarDescription*>::const_iterator iter = find( name );
  map<string,VarDescription*>::const_iterator iend = end();
  if ( iter == iend ) return;
  VarDescription* vd = iter->second;
  // create names for histograms
  string sigName = "hSig_" + name;
  string bkgName = "hBkg_" + name;
  // create histograms
  vd->sigHisto = new TH1F( sigName.c_str(), sigName.c_str(), nb, xmin, xmax );
  vd->bkgHisto = new TH1F( bkgName.c_str(), bkgName.c_str(), nb, xmin, xmax );
  return;
}


// fill histograms for "signal" or "background" events
void DiscriminatorFill::fill( DiscriminatorClassification::Type type ) {
  // loop over quantities
  for ( const auto& element: *this ) {
    VarDescription* vd = element.second;
    // skip unused quantities
    if ( !vd->use ) continue;
    // fill histograms
    fill( vd, type );
  }
  return;

}


// fill histograms for a specific quantity
void DiscriminatorFill::fill( DiscriminatorBase::VarDescription* vd,
                              DiscriminatorClassification::Type type ) {
  switch ( type ) {
  case DiscriminatorClassification::signal:
    // fill histograms for signal
    vd->sigHisto->Fill( *vd->content );
    break;
  case DiscriminatorClassification::background:
    // fill histograms for background
    vd->bkgHisto->Fill( *vd->content );
    break;
  }

}


// save histograms for "signal" or "background" events
void DiscriminatorFill::save( const string& name ) {
  // save current working area
  TDirectory* currentDir = gDirectory;
  // open file
  TFile* file = new TFile( name.c_str(), "RECREATE" );
  // loop over quantities
  map<string,VarDescription*>::const_iterator iter = begin();
  map<string,VarDescription*>::const_iterator iend = end();
  while ( iter != iend ) {
    // get quantity informations
    const map<string,VarDescription*>::value_type& element = *iter++;
    VarDescription* vd = element.second;
    // skip unused quantities
    if ( !vd->use ) continue;
    // normalize histograms
    normalizeHisto( vd->sigHisto );
    normalizeHisto( vd->bkgHisto );
    // save histograms
    vd->sigHisto->Write();
    vd->bkgHisto->Write();
  }
  // close file
  file->Close();
  delete file;
  // restore working area
  currentDir->cd();
  return;
}


// normalize histogram to have s=1 with s=sum of bin content
void DiscriminatorFill::normalizeHisto( TH1F* h ) {
  // initialize sum of contents
  float sum = 0;
  // loop over bins and sum contents
  int i;
  int n = h->GetNbinsX() + 2;
  for ( i = 0; i < n; ++i ) sum += h->GetBinContent( i );
  // loop over bins and divide content by the sum
  for ( i = 0; i < n; ++i ) {
    h->SetBinContent( i,
    h->GetBinContent( i ) / sum );
    h->SetBinError  ( i,
    h->GetBinError  ( i ) / sum );
  }
  return;
}


