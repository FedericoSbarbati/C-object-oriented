#include <iostream>
#include <fstream>

using namespace std;

int read(ifstream &file,
         float &x, float &y, float &z,
         int *charge,
         float *px, float *py, float *pz)
{
   file >> x >> y >> z;
   int n;
   file >> n;
    for(int i = 0; i < n; ++i)
    {
       file >> charge[i];
       file >> px[i];
       file >> py[i];
       file >> pz[i];
    }
    return n;
}