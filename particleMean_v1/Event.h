#ifndef EVENT_H
#define EVENT_H


struct Particle {
int charge; 
float px,py,pz; 
};

struct Event {
float x,y,z;
int nParticle;
int evNumber;
Particle** part;
};

#endif

