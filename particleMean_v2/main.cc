#include <iostream>
#include <fstream>

#include "Event.h"
#include "MassMean.h"
#include "Constants.h"
#include "Utilities.h"

const Event *read(std::ifstream &file);
void dump(const Event &ev);

using namespace std;

int main(int argc, char *argv[])
{
    // open input file
    const char *name = argv[1];
    std::ifstream file(name);

    // creating MassMean instance
    MassMean k(0.495, 0.500);
    MassMean lambda(1.115, 1.116);

    // loop over events

    const Event *ev;
    while ((ev = read(file)) != nullptr)
    {
        //dump(*ev);
        k.add(*ev);
        lambda.add(*ev);
        delete ev;
    }

    k.compute();
    lambda.compute();

    cout << endl;
    cout << "Results for Lambda0: " << endl;
    cout << "Number of accepted events: " << lambda.getNacceptedEv() << endl;
    cout << "Mean: " << lambda.getMean() << endl;
    cout << "RMS: " << lambda.getRMS() << endl;
    cout << endl << endl;

    cout << "Results for K0: " << endl;
    cout << "Number of accepted events: " << k.getNacceptedEv() << endl;
    cout << "Mean: " << k.getMean() << endl;
    cout << "RMS: " << k.getRMS() << endl;
    cout << endl << endl;

    return 0;
}