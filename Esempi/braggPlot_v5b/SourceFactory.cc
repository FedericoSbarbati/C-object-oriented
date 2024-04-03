#include "SourceFactory.h"
#include "AnalysisInfo.h"

#include "EventReadFromFile.h"
#include "EventSim.h"

#include <iostream>
#include <sstream>

using namespace std;

SourceFactory::SourceFactory() {
}


SourceFactory::~SourceFactory() {
}


// create event source
EventSource* SourceFactory::create( const AnalysisInfo* info ) {
  if ( info->contains( "input" ) ) {
    char m = *info->value( "imode" ).c_str();
    if ( m == 'A' ) m = 'a';
    return new EventReadFromFile( info->value( "input" ),
                                  m == 'a' ? std::ios::in : std::ios::binary );
  }
  if ( info->contains( "sim"   ) ) {
    stringstream sstr;
    // get number of events to generate
    sstr.str( info->value( "sim" ) );
    unsigned int nevt;
    sstr >> nevt;
    // set seed if available
    unsigned int seed = 1;
    if ( info->contains( "seed" ) ) {
      sstr.clear();
      sstr.str( info->value( "seed" ) );
      sstr >> seed;
    }
    return new EventSim( nevt, seed );
  }
  return nullptr;
}

