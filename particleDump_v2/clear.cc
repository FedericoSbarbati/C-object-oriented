#include "Event.h"

// Function to clear the memory allocated to an Event object
void clear(const Event *ev)
{
    // Loop over each particle in the event
    for (int i = 0; i < ev->nParticle; i++)
    {
        delete ev->part[i]; // Delete the particle object
    }
    delete[] ev->part; // Delete the array of particle pointers
    delete ev;         // Delete the event object

    return;
}