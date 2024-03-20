#include <iostream>
#include <fstream>
#include <cmath>

#include "Event.h"
using namespace std;

const Event *read(std::ifstream &file);
void dump(const Event &ev);
void clear(const Event *ev);
bool add(const Event& ev, double min, double MAX,double& invMsum, double& squareSum);

int main(int argc, char *argv[])
{
    // Open input file
    const char *name = argv[1];
    std::ifstream file(name, std::ios::binary);
    if (!file)
    {
        std::cerr << "Errore nell'apertura del file: " << name << std::endl;
        return 1;
    }

    //Declaring variables
    int nAccepted = 0;
    double invMsum = 0;
    double squareSum = 0;
    double mean;
    double RMS;

    double min = 0.490;
    double max = 0.505;


    const Event* ev;
    while ((ev = read(file)) != nullptr)
    {
        //dump(*ev); //Disabling dump of the events
        if(add(*ev,min,max,invMsum,squareSum))
        {
            nAccepted++;
        }
        clear(ev);
    }

    mean = invMsum/((double)nAccepted);
    RMS = sqrt(squareSum/ ((double)nAccepted)- mean*mean);

    mean += min;

    cout << "Mean: " << mean << endl;
    cout << "RMS: " << RMS << endl;
    //cout << "Square sum: " << squareSum << endl;
    cout << "nAccepted: " << nAccepted << endl;

    return 0;
}