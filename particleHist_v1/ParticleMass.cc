#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>


#include "ParticleMass.h"
#include "Event.h"
#include "MassMean.h"
#include "TH1F.h"


using namespace std;

ParticleMass::ParticleMass()
{
}

ParticleMass::~ParticleMass()
{
}

// create objects for a Bragg curve
void ParticleMass::pCreate(const string &name, float min, float max)
{
    // create name for TH1F object
    const char *hName = name.c_str();

    // bin number equal to point number
    //int nBinD = Event::minSize;

    // create TH1F and statistic objects and store their pointers
    Particle* p = new Particle;
    p->name = name;
    p->mMean = new MassMean(min,max);
    p->hMean = new TH1F();
    p->hMean->SetName(hName);
    p->hMean->SetTitle(hName);
    pList.push_back(p);

    return;
}

void ParticleMass::beginJob()
{
    pList.reserve(2);

    // creating Particles instances

    pCreate("")

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