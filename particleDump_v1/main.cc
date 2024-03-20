#include <iostream>
#include <fstream>

using namespace std;

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
    if (!file)
    {
        cerr << "Errore nell'apertura del file: " << name << endl;
        return 1;
    }

    // Declaring event variables
    int evNumber;
    int nParticles;
    float x;
    float y;
    float z;
    int charges[10];
    float px[10];
    float py[10];
    float pz[10];

    // Loop over events
    while (file >> evNumber)
    {
        nParticles = read(file, x, y, z, charges, px, py, pz);
        dump(evNumber, nParticles, x, y, z, charges, px, py, pz);
    }

    return 0;
}
