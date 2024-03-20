#ifndef Event_h
#define Event_h

class Event
{

public:
  // constructor
  Event(int n, float x, float y, float z); // create an event with number "n"
                                           // and coordinates x, y, z
  // destructor
  ~Event();

  // composite object Particle to hold all information for each particle
  // ( electric charge and x,y,z momentum components )
  struct Particle
  {
    int charge;
    float px, py, pz;
  };
  typedef const Particle *part_ptr;

  // add a particle to the event
  void add(int charge, float px, float py, float pz);

  // get event id.
  int eventNumber() const;

  // get decay point coordinates
  float getX() const;
  float getY() const;
  float getZ() const;

  // get number of particles
  int getnParticle() const;

  // get particle
  part_ptr particle(unsigned int i) const;

private:
  // event-specific informations:
  // event id
  // decay point
  // particles: number and array of pointers

  int evNumber;
  float x, y, z;
  unsigned int nParticle;
  Particle **part;

  // shared variables to contain max number of particles
  static const unsigned int maxSize;
};

#endif
