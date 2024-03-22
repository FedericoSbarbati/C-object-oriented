#include "EventDiscriminator.h"
#include "Event.h"

#include "TH1F.h"
#include "TFile.h"

#include <cmath>

using namespace std;

EventDiscriminator::EventDiscriminator() {
}


EventDiscriminator::~EventDiscriminator() {
}


// create histograms
void EventDiscriminator::book() {
  hSig_chi2     = new TH1F( "hSig_chi2"    , "hSig_chi2"    ,  4, 0.0, 40.0 );
  hBkg_chi2     = new TH1F( "hBkg_chi2"    , "hBkg_chi2"    ,  4, 0.0, 40.0 );
  hSig_muoKink  = new TH1F( "hSig_muoKink" , "hSig_muoKink" ,  7, 0.0, 70.0 );
  hBkg_muoKink  = new TH1F( "hBkg_muoKink" , "hBkg_muoKink" ,  7, 0.0, 70.0 );
  hSig_trkKink  = new TH1F( "hSig_trkKink" , "hSig_trkKink" ,  4, 0.0, 20.0 );
  hBkg_trkKink  = new TH1F( "hBkg_trkKink" , "hBkg_trkKink" ,  4, 0.0, 20.0 );
  hSig_deltaEta = new TH1F( "hSig_deltaEta", "hSig_deltaEta",  5, 0.0, 0.25 );
  hBkg_deltaEta = new TH1F( "hBkg_deltaEta", "hBkg_deltaEta",  5, 0.0, 0.25 );
  hSig_muoComp  = new TH1F( "hSig_muoComp" , "hSig_muoComp" ,  5, 0.0,  1.0 );
  hBkg_muoComp  = new TH1F( "hBkg_muoComp" , "hBkg_muoComp" ,  5, 0.0,  1.0 );
  hSig_muoSum   = new TH1F( "hSig_muoSum"  , "hSig_muoSum"  , 10, 0.0, 50.0 );
  hBkg_muoSum   = new TH1F( "hBkg_muoSum"  , "hBkg_muoSum"  , 10, 0.0, 50.0 );
}


// fill histograms for "signal" or "background" events
void EventDiscriminator::fill( const Event& ev ) {

  // compute event variables
  compute( ev );
  switch ( ev.evType() ) {
  case Event::signal:
    // fill histograms for "signal" events
    hSig_chi2    ->Fill( chi2     );
    hSig_muoKink ->Fill( muoKink  );
    hSig_trkKink ->Fill( trkKink  );
    hSig_deltaEta->Fill( deltaEta );
    hSig_muoComp ->Fill( muoComp  );
    hSig_muoSum  ->Fill( muoSum   );
    break;
  case Event::background:
    // fill histograms for "background" events
    hBkg_chi2    ->Fill( chi2     );
    hBkg_muoKink ->Fill( muoKink  );
    hBkg_trkKink ->Fill( trkKink  );
    hBkg_deltaEta->Fill( deltaEta );
    hBkg_muoComp ->Fill( muoComp  );
    hBkg_muoSum  ->Fill( muoSum   );
    break;
  }
  return;

}


// save histograms
void EventDiscriminator::save( const string& name ) {
  // save current working area
  TDirectory* currentDir = gDirectory;
  // open file
  TFile* file = new TFile( name.c_str(), "RECREATE" );
  // normalize histograms for "signal" events
  normalizeHisto( hSig_chi2     );
  normalizeHisto( hSig_muoKink  );
  normalizeHisto( hSig_trkKink  );
  normalizeHisto( hSig_deltaEta );
  normalizeHisto( hSig_muoComp  );
  normalizeHisto( hSig_muoSum   );
  // save histograms for "signal" events
  hSig_chi2    ->Write();
  hSig_muoKink ->Write();
  hSig_trkKink ->Write();
  hSig_deltaEta->Write();
  hSig_muoComp ->Write();
  hSig_muoSum  ->Write();
  // normalize histograms for "background" events
  normalizeHisto( hBkg_chi2     );
  normalizeHisto( hBkg_muoKink  );
  normalizeHisto( hBkg_trkKink  );
  normalizeHisto( hBkg_deltaEta );
  normalizeHisto( hBkg_muoComp  );
  normalizeHisto( hBkg_muoSum   );
  // save histograms for "background" events
  hBkg_chi2    ->Write();
  hBkg_muoKink ->Write();
  hBkg_trkKink ->Write();
  hBkg_deltaEta->Write();
  hBkg_muoComp ->Write();
  hBkg_muoSum  ->Write();
  // close file
  file->Close();
  delete file;
  // restore working area
  currentDir->cd();
  return;
}


void EventDiscriminator::read( const string& name ) {
  // save current working area
  TDirectory* currentDir = gDirectory;
  // open file
  TFile* file = new TFile( name.c_str() );
  // restore working area
  currentDir->cd();
  // read and copy histograms
  hSig_chi2     = dynamic_cast<TH1F*>( file->Get( "hSig_chi2"     )->Clone() );
  hSig_muoKink  = dynamic_cast<TH1F*>( file->Get( "hSig_muoKink"  )->Clone() );
  hSig_trkKink  = dynamic_cast<TH1F*>( file->Get( "hSig_trkKink"  )->Clone() );
  hSig_deltaEta = dynamic_cast<TH1F*>( file->Get( "hSig_deltaEta" )->Clone() );
  hSig_muoComp  = dynamic_cast<TH1F*>( file->Get( "hSig_muoComp"  )->Clone() );
  hSig_muoSum   = dynamic_cast<TH1F*>( file->Get( "hSig_muoSum"   )->Clone() );
  hBkg_chi2     = dynamic_cast<TH1F*>( file->Get( "hBkg_chi2"     )->Clone() );
  hBkg_muoKink  = dynamic_cast<TH1F*>( file->Get( "hBkg_muoKink"  )->Clone() );
  hBkg_trkKink  = dynamic_cast<TH1F*>( file->Get( "hBkg_trkKink"  )->Clone() );
  hBkg_deltaEta = dynamic_cast<TH1F*>( file->Get( "hBkg_deltaEta" )->Clone() );
  hBkg_muoComp  = dynamic_cast<TH1F*>( file->Get( "hBkg_muoComp"  )->Clone() );
  hBkg_muoSum   = dynamic_cast<TH1F*>( file->Get( "hBkg_muoSum"   )->Clone() );
  // close file
  file->Close();
  delete file;
  return;
}


// compute discriminating variable for an event
float EventDiscriminator::get( const Event& ev ) {
  // compute event variables
  compute( ev );
  // initialize probabilities
  float dSig = 0.5;
  // update probabilities for each variable
  get( chi2    , dSig, hSig_chi2    , hBkg_chi2     );
  get( muoKink , dSig, hSig_muoKink , hBkg_muoKink  );
  get( trkKink , dSig, hSig_trkKink , hBkg_trkKink  );
  get( deltaEta, dSig, hSig_deltaEta, hBkg_deltaEta );
  get( muoComp , dSig, hSig_muoComp , hBkg_muoComp  );
  get( muoSum  , dSig, hSig_muoSum  , hBkg_muoSum   );
  // return discriminating variable
  return dSig;
}


// normalize histogram to have s=1 with s=sum of bin content
void EventDiscriminator::normalizeHisto( TH1F* h ) {
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


// compute event variables
void EventDiscriminator::compute( const Event& ev ) {
  float x  = ev.muoX();
  float y  = ev.muoY();
  float a  = ev.muoA();
  float b  = ev.muoB();
  chi2     = sqrt( x * y );
  muoKink  = sqrt( x / y );
  if ( muoKink > 60.0 ) muoKink = ( muoKink / 4.0 ) + 45.0;
  trkKink  = log( ev.trkKink() );
  if ( trkKink > 15.0 ) trkKink = ( trkKink / 3.0 ) + 10.0;
  deltaEta = ev.muoEta2() - ev.muoEta1();
  muoComp  = ( a + b ) / 2.0;
  muoSum   = ( a - b ) / 2.0;
  if ( muoSum > 42.0 ) muoSum = ( muoSum / 6.0 ) + 35.0;
  return;
}


// compute probabilities for a variable
void EventDiscriminator::get( float x, float& dSig,
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

