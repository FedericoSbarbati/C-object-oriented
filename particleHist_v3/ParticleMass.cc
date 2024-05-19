#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

// root classes include files
#include "TH1F.h"
#include "TFile.h"
#include "TDirectory.h"

#include "Event.h"
#include "MassMean.h"
#include "AnalysisInfo.h"
#include "AnalysisFactory.h"
#include "ParticleMass.h"

double mass(const Event &ev);

using namespace std;

// concrete factory to create a ParticleMass analyzer
class ParticleMassFactory : public AnalysisFactory::AbsFactory
{
public:
    // assign "plot" as name for this analyzer and factory
    ParticleMassFactory() : AnalysisFactory::AbsFactory("plot") {}

    // create an ParticleMass when builder is run
    AnalysisSteering *create(const AnalysisInfo *info) override // See AnalysisFactory::create(info)
    {
        return new ParticleMass(info);
    }
};

static ParticleMassFactory pm;

ParticleMass::ParticleMass(const AnalysisInfo *info) : AnalysisSteering(info)
{
}

ParticleMass::~ParticleMass()
{
}

void ParticleMass::pCreate(const string &name, float min, float max)
{
    // create name for TH1F object
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
    p->hMean = new TH1F(hName, hTitle, nBins, min, max);
    p->hMean->SetFillColor(kBlue);
    pList.push_back(p);

    return;
}

void ParticleMass::beginJob()
{
    pList.reserve(2);

    // creating Particle instances
    pCreate("K0", 0.495, 0.500);
    pCreate("LAMBDA0", 1.115, 1.116);

    return;
}

void ParticleMass::endJob()
{
    // save current working area
    TDirectory *currentDir = gDirectory;

    // open histogram file
    TFile *file = new TFile(aInfo->value("plot").c_str(), "CREATE"); // RECREATE

    if (file->IsZombie())
    {
        cerr << "Error opening file with name: " << aInfo->value("plot") << endl;
        delete file;
        return;
    }

    // loop over MassMean objects
    for (Particle *p : pList)
    {
        MassMean *statMean = p->mMean;
        TH1F *hist = p->hMean;

        // Data evaluation
        statMean->compute();

        // Printing results:
        cout << endl;
        cout << "Particle: " << p->name << endl;
        cout << "Mean: " << statMean->getMean() << endl;
        cout << "RMS: " << statMean->getRMS() << endl;
        cout << "Number of accepted Events: " << statMean->getNacceptedEv() << endl;
        cout << endl;

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
            p->hMean->Fill(invM);
        }
    }
    return;
}