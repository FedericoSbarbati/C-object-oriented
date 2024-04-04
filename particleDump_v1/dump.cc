#include <iostream>

using namespace std;

// This function dumps the event data to the console.
void dump(int evNumber,                    // Event number
          int nParticles,                  // Number of particles
          float &x, float &y, float &z,    // Reference variables for the coordinates
          int *charges,                    // Pointer to an array of charges
          float *px, float *py, float *pz) // Pointers to arrays of particle coordinates
{
    // Print the event number
    cout << evNumber << endl;
    // Print the number of particles
    cout << nParticles << endl;
    // Print the coordinates
    cout << x << ' ' << y << ' ' << z << endl;

    // Loop over each particle
    for (int i = 0; i < nParticles; ++i)
    {
        // Print the charge and coordinates of the particle
        cout << ' ' << charges[i] << ' '
             << px[i] << ' ' << py[i] << ' ' << pz[i] << endl;
    }

    return;
}