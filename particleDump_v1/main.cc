#include <iostream>
#include <fstream>

using namespace std;

// Function prototypes
int read(ifstream &file,
         float &x, float &y, float &z,
         int *charge,
         float *px, float *py, float *pz);

void dump(int evNumber,
          int nParticles,
          float &x, float &y, float &z,
          int *charges,
          float *px, float *py, float *pz);

int main(int argc, char *argv[])
{
    // Open input file
    const char *name = argv[1];
    ifstream file(name, std::ios::binary);

    // Check if file opened successfully
    if (!file)
    {
        cerr << "Error opening file: " << name << endl;
        return 1;
    }

    // Declare variables for event data
    int evNumber;
    int nParticles;
    float x;
    float y;
    float z;
    int charges[10];
    float px[10];
    float py[10];
    float pz[10];

    // Loop over events in the file
    while (file >> evNumber)
    {
        // Read event data from file
        nParticles = read(file, x, y, z, charges, px, py, pz);
        // Dump event data to console
        dump(evNumber, nParticles, x, y, z, charges, px, py, pz);
    }

    return 0;
}