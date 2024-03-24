#include "Event.h"
#include "EventDiscriminatorRead.h"
#include "DiscAnalysis.h"

#include "TH1F.h"
#include "TFile.h"

using namespace std;

DiscAnalysis::DiscAnalysis() {
}


DiscAnalysis::~DiscAnalysis() {
}


void DiscAnalysis::init( const string& name ) {
  disc = new EventDiscriminatorRead;
  disc->read( name );
  h_dSig = new TH1F( "h_dSig", "h_dSig", 20, 0.0, 1.0 );
  h_dBkg = new TH1F( "h_dBkg", "h_dBkg", 20, 0.0, 1.0 );
}


void DiscAnalysis::analyze( const Event& ev ) {
  ( ev.evType() == DiscriminatorClassification::signal ?
    h_dSig :
    h_dBkg )->Fill( disc->get( ev ) );
  return;
}


void DiscAnalysis::save( const string& name ) {
  TDirectory* currentDir = gDirectory;
  TFile* file = new TFile( name.c_str(), "RECREATE" );
  h_dSig->Write();
  h_dBkg->Write();
  file->Close();
  delete file;
  currentDir->cd();
  return;
}

