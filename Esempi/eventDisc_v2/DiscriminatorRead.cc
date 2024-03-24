#include "DiscriminatorRead.h"

#include "TH1F.h"
#include "TFile.h"

using namespace std;

DiscriminatorRead::DiscriminatorRead() {
}


DiscriminatorRead::~DiscriminatorRead() {
}


// read histograms for specific quantity
void DiscriminatorRead::read( const string& name ) {
  // save current working area
  TDirectory* currentDir = gDirectory;
  // open file
  TFile* file = new TFile( name.c_str() );
  // restore working area
  currentDir->cd();
  // loop over quantities
  string sigName;
  string bkgName;
  for ( const auto& element: *this ) {
    VarDescription* vd = element.second;
    // skip unused quantities
    if ( !vd->use ) continue;
    // create names for histograms
    sigName = "hSig_" + element.first;
    bkgName = "hBkg_" + element.first;
    // read and copy histograms
    vd->sigHisto = dynamic_cast<TH1F*>( file->Get( sigName.c_str() )->Clone() );
    vd->bkgHisto = dynamic_cast<TH1F*>( file->Get( bkgName.c_str() )->Clone() );
  }
  // close file
  file->Close();
  delete file;
  return;
}

