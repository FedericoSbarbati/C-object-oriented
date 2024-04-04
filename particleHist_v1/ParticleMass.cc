#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

#include "ParticleMass.h"
#include "Event.h"
#include "MassMean.h"
#include "TH1F.h"
#include "TFile.h"
#include "TDirectory.h"

double mass(const Event &ev);
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
    // create name and title for TH1F object
    string label = " invariant Mass hist; M[Gev/c^{2}]; Occurrences";
    string title = name + label;
    const char *hName = name.c_str();
    const char *hTitle = title.c_str();

    // Setting bin number constant
    int nBins = 150;
    
    // create TH1F and statistic objects and store their pointers
    Particle *p = new Particle;
    p->name = name;
    p->mMean = new MassMean(min, max);
    p->hMean = new TH1F(hName,hTitle,nBins,min,max);
    p->hMean->SetFillColor(kBlue);
    pList.push_back(p);

    return;
}

void ParticleMass::beginJob()
{
    pList.reserve(2);

    // creating Particles instances
    pCreate("K0", 0.495, 0.500);
    pCreate("LAMBDA0", 1.115, 1.116);

    return;
}

void ParticleMass::endJob()
{
    // save current working area
    TDirectory *currentDir = gDirectory;
    // open histogram file
    TFile *file = new TFile("hist.root", "RECREATE");

    // loop over MassMean objects
    for (Particle *p : pList)
    {
        MassMean *statMean = p->mMean;
        TH1F *hist = p->hMean;

        // Data evalution
        statMean->compute();

        // Printing results:
        cout << endl
             << endl;
        cout << "Mean: " << statMean->getMean() << endl;
        cout << "RMS: " << statMean->getRMS() << endl;
        cout << "Number of accepted Events: " << statMean->getNacceptedEv() << endl;
        cout << endl
             << endl;

        hist->Write();
    }

    file->Close();
    delete file;
    // Restoring working area;
    currentDir->cd();

    return;
}

void ParticleMass::process(const Event &ev)
{
    // adding event to all the MassMean instances
    for (Particle *p : pList)
    {
        if (p->mMean->add(ev))
        {
            double invM = mass(ev);
            p->hMean->Fill(invM); // Fill the histogram with the invariant mass
        }
    }
    return;
}