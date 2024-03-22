#include "ParticleMass.h"
#include "Event.h"
#include "MassMean.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

ParticleMass::ParticleMass()
{
}

ParticleMass::~ParticleMass()
{
}

void ParticleMass::beginJob()
{
    pList.reserve(2);

    // creating MassMean instance
    pList.push_back(new MassMean(0.495, 0.500));
    pList.push_back(new MassMean(1.115, 1.116));

    return;
}

void ParticleMass::endJob()
{

    // loop over MassMean objects
    for (MassMean *mMean : pList)
    {
        mMean->compute();
        // Printing results:
        cout << endl
             << endl;
        cout << "Mean: " << mMean->getMean() << endl;
        cout << "RMS: " << mMean->getRMS() << endl;
        cout << "Number of accepted Events: " << mMean->getNacceptedEv() << endl;
        cout << endl
             << endl;
    }

    return;
}

void ParticleMass::process(const Event &ev)
{
    // adding event to all the MassMean instances
    for (MassMean *mMean : pList)
    {
        mMean->add(ev);
    }
    return;
}