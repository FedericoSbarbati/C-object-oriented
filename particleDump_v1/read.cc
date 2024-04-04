#include <iostream>
#include <fstream>

using namespace std;
// This function reads data from a file into several variables.
int read(ifstream &file,                  // Input file stream
         float &x, float &y, float &z,    // Reference variables to store the decay points
         int *charge,                     // Pointer to an array to store charge of particles
         float *px, float *py, float *pz) // Pointers to arrays to store momentum components
{
   // Read the decay point coordinates from the file
   file >> x >> y >> z;

   int n;
   // Read the number of particles in the event from the file
   file >> n;

   // Loop over the particles in the event
   for (int i = 0; i < n; ++i)
   {

      // Read the charge and momentum components of the particle from the file
      file >> charge[i];
      file >> px[i];
      file >> py[i];
      file >> pz[i];
   }

   // Return the number of particles in the event
   return n;
}