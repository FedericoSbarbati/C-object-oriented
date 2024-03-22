#include <iostream>
#include <fstream>

#include "Event.h"

using namespace std;

const Event* read( ifstream& file ) {

  Event* ev;
  int i;
  float x;
  float y;
  float k;
  float e1;
  float e2;
  float a;
  float b;
  int   evType  ;
  // try to read input file
  if ( file >> i >> x >> y >> k >> e1 >> e2 >> a >> b >> evType )
       ev = new Event( i, x, y, k, e1, e2, a, b, evType );
  else return nullptr;

  return ev;

}

