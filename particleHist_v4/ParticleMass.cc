#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

// root classes include files
#include "TH1F.h"
#include "TFile.h"
#include "TDirectory.h"
#include "util/include/TFileProxy.h"

#include "Event.h"
#include "MassMean.h"
#include "AnalysisInfo.h"
#include "AnalysisFactory.h"
#include "ParticleMass.h"
#include "ParticleReco.h"

using namespace std;

// concrete factory to create an ElementReco analyzer
class ParticleMassFactory : public AnalysisFactory::AbsFactory
{
public:
    // assign "plot" as name for this analyzer and factory
    ParticleMassFactory() : AnalysisFactory::AbsFactory("plot") {}
    // create an ElementReco when builder is run
    AnalysisSteering *create(const AnalysisInfo *info) override
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
    TFileProxy* file = new TFileProxy(aInfo->value("plot").c_str(), "CREATE"); // RECREATE
    if (!file)
    {
        cerr << "Error opening file with name: " << aInfo->value("plot") << endl;
        delete file;
        return;
    }

    // loop over ParticleMass::Particle objects
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

void ParticleMass::update(const Event &ev)
{
    // adding event to all the MassMean instances
    for (Particle *p : pList)
    {
        if (p->mMean->add(ev))
        {
            static ParticleReco *ener = ParticleReco::instance();
            double invM = ener->getParticleMass();
            p->hMean->Fill(invM);
        }
    }
    return;
}