#include <iostream>

using namespace std;

void dump(int evNumber,
          int nParticles,
          float &x, float &y, float &z,
          int *charges,
          float *px, float *py, float *pz)
{

    cout << evNumber << endl;
    cout << nParticles << endl;
    cout << x << ' ' << y << ' ' << z << endl;

    for (int i = 0; i < nParticles; ++i)
    {
        cout << ' ' << charges[i] << ' '
             << px[i] << ' ' << py[i] << ' ' << pz[i] << endl;
    }
    return;
}