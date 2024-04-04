#ifndef EVENT_H
#define EVENT_H

// Structure to represent a Particle
struct Particle
{
    int charge;       // Variable to hold the charge of the particle
    float px, py, pz; // Variables to hold the momentum components of the particle
};

// Structure to represent an Event
struct Event
{
    float x, y, z;   // Variables to hold the x, y, z coordinates of the event
    int nParticle;   // Variable to hold the number of particles in the event
    int evNumber;    // Variable to hold the event number
    Particle **part; // Pointer to an array of pointers to Particle objects
};

#endif
