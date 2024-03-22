#ifndef DiscAnalysis_h
#define DiscAnalysis_h

#include <string>

class Event;
class EventDiscriminator;
class TH1F;

class DiscAnalysis {

 public:

  DiscAnalysis();
  // deleted copy constructor and assignment to prevent unadvertent copy
  DiscAnalysis           ( const DiscAnalysis& x ) = delete;
  DiscAnalysis& operator=( const DiscAnalysis& x ) = delete;

  ~DiscAnalysis();

  void init( const std::string& name );
  void analyze( const Event& ev ); // analyze a new event
  void save( const std::string& name );

 private:

  // discriminator object and histogram
  EventDiscriminator* disc;
  TH1F* h_dSig;
  TH1F* h_dBkg;

};

#endif

