#ifndef Event_h
#define Event_h

class Event {

 public:

  enum Type { signal, background };

  Event( int n,
         float x,
         float y,
         float k,
         float e1,
         float e2,
         float a,
         float b,
	 int   t ):
   evNumber( n ),
   pX  ( x  ),
   pY  ( y  ),
   pK  ( k  ),
   pE1 ( e1 ),
   pE2 ( e2 ),
   pA  ( a  ),
   pB  ( b  ),
   pType ( t ? signal : background ) {
  }

  // default copy constructor and assignment
  Event           ( const Event& x ) = default;
  Event& operator=( const Event& x ) = default;

  ~Event() {
  }

  // return event id.
  int eventNumber() const { return evNumber; }

  // return data
  float muoX   () const { return pX; }
  float muoY   () const { return pY; }
  float trkKink() const { return pK; }
  float muoEta1() const { return pE1; }
  float muoEta2() const { return pE2; }
  float muoA   () const { return pA; }
  float muoB   () const { return pB; }

  // return event type
  Type  evType  () const { return pType; }

 private:

  // event identifier
  int evNumber;    // event id

  float pX;  // chi square / muon kink - X
  float pY;  // chi square / muon kink - Y
  float pK;  // track kink
  float pE1; // pseudorapidity 1
  float pE2; // pseudorapidity 2
  float pA;  // muon compatibility / energy sum - A
  float pB;  // muon compatibility / energy sum - B

  // event type
  Type pType;

};

#endif

