#ifndef Event_h
#define Event_h

#include <vector>

class Event {

 public:

  // create event with number "n"
  Event( int n );
  // deleted copy constructor and assignment to prevent unadvertent copy
  Event           ( const Event& x ) = delete;
  Event& operator=( const Event& x ) = delete;

  ~Event();

  // function to add a point
  void add( int energyLoss );

  // get event-specific informations:
  //   event number
  //   number of points in the event
  //   energy for point "i"
  int eventNumber() const;
  unsigned int dataSize() const;
  int energy( unsigned int i ) const;

  // shared variables to contain min and max number of points
  static const unsigned int minSize;
  static const unsigned int maxSize;

 private:

  // event-specific informations:
  //   event number
  //   array with energies
  int evNumber;
  std::vector<int> eLoss;

};

#endif

