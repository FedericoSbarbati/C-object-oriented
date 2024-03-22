#ifndef EventDiscriminator_h
#define EventDiscriminator_h

#include <string>

class TH1F;

class Event;

class EventDiscriminator {

 public:

  EventDiscriminator();
  // deleted copy constructor and assignment to prevent unadvertent copy
  EventDiscriminator           ( const EventDiscriminator& x ) = delete;
  EventDiscriminator& operator=( const EventDiscriminator& x ) = delete;

  ~EventDiscriminator();

  // create histograms
  void book();

  // fill histograms for "signal" or "background" events
  void fill( const Event& ev );
  // save histograms for "signal" or "background" events
  void save( const std::string& name );
  // read all histograms
  void read( const std::string& name );

  // compute discriminating variable for an event
  float get( const Event& ev );

 private:

  // normalize histogram to have s=1 with s=sum of bin content
  void normalizeHisto( TH1F* h );
  // compute event variables
  void compute( const Event& ev );
  // compute probabilities for a variable
  void get( float x, float& dSig,
            TH1F* hSig, TH1F* hBkg );
  // event variables
  float chi2    ;
  float muoKink ;
  float trkKink ;
  float deltaEta;
  float muoComp ;
  float muoSum  ;

  // histograms for signal
  TH1F* hSig_chi2    ;
  TH1F* hSig_muoKink ;
  TH1F* hSig_trkKink ;
  TH1F* hSig_deltaEta;
  TH1F* hSig_muoComp ;
  TH1F* hSig_muoSum  ;
  // histograms for background
  TH1F* hBkg_chi2    ;
  TH1F* hBkg_muoKink ;
  TH1F* hBkg_trkKink ;
  TH1F* hBkg_deltaEta;
  TH1F* hBkg_muoComp ;
  TH1F* hBkg_muoSum  ;

};

#endif

