#include <iostream>
#include <fstream>
#include <string>

#include "DiscAnalysis.h"
#include "Event.h"

using namespace std;

const Event* read( ifstream& file );

int main( int argc, char* argv[] ) {

  // save command parameters
  string name = argv[1];
  string hd_i = argv[2];
  string hist = argv[3];

  // open input file
  ifstream file( name.c_str() );

  // objects for discriminator analysis
  DiscAnalysis disc;
  disc.init( hd_i );

  cout << "read events" << endl;
  // loop over events
  const Event* ev;
  while ( ( ev = read( file ) ) != nullptr ) {
    disc.analyze( *ev );
    delete ev;
  }

  disc.save( hist );

  return 0;

}

