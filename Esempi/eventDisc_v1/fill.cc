#include <iostream>
#include <fstream>
#include <string>

#include "EventDiscriminator.h"
#include "Event.h"

using namespace std;

const Event* read( ifstream& file );

int main( int argc, char* argv[] ) {

  // open input file
  string name = argv[1];
  ifstream file( name.c_str() );
  string hist = argv[2];

  // objects to fill discriminator distributions
  EventDiscriminator disc;
  disc.book();

  cout << "read events" << endl;
  // loop over events
  int count = 0;
  const Event* ev;
  while ( ( ev = read( file ) ) != nullptr ) {
    disc.fill( *ev );
    ++count;
    delete ev;
  }
  cout << count << " events read" << endl;

  disc.save( hist );

  return 0;

}

