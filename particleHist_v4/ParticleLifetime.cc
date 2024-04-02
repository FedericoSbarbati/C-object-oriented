#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

// root classes include files
#include "TH1F.h"
#include "TFile.h"
#include "TDirectory.h"

#include "Event.h"
#include "AnalysisInfo.h"
#include "AnalysisFactory.h"
#include "ParticleLifetime.h"
#include "LifetimeFit.h"
#include "ProperTime.h"


using namespace std;

// concrete factory to create an analyzer
class ParticleLifetimeFactory : public AnalysisFactory::AbsFactory
{
public:
    // assign "plot" as name for this analyzer and factory
    ParticleLifetimeFactory() : AnalysisFactory::AbsFactory("plot") {}
    // create an ElementReco when builder is run
    AnalysisSteering *create(const AnalysisInfo *info) override
    {
        return new ParticleLifetime(info);
    }
};

static ParticleLifetimeFactory tm;

ParticleLifetime::ParticleLifetime(const AnalysisInfo *info) : AnalysisSteering(info)
{
}

ParticleLifetime::~ParticleLifetime()
{
}


void ParticleLifetime::pCreate(const string &name, float min, float max, float timeMin, float timeMax)
{
    // create name for TH1F object
    string label = " time";
    string title = name + label;
    const char *hName = name.c_str();
    const char *hTitle = title.c_str();

    // Setting bin number constant
    int nBins = 150;

    // create TH1F and statistic objects and store their pointers
    Particle *p = new Particle;
    p->name = name;
    p->tMean = new LifetimeFit(timeMin, timeMax);
    p->hMean = new TH1F(hName, hTitle, nBins, timeMin, timeMax);
    p->hMean->SetFillColor(kRed);
    pList.push_back(p);

    return;
}

void ParticleLifetime::beginJob()
{
    pList.reserve(2);

    // creating Particles instances
    pCreate("K^{0}_{s}", 0.495, 0.500,10.0,500.0);
    pCreate("#Lambda_{0}", 1.115, 1.116,10.0,1000.0);

    return;
}

void ParticleLifetime::endJob()
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

    // loop over ParticleLifetime::Particle objects
    for (Particle *p : pList)
    {
        TH1F *hist = p->hMean;
        LifetimeFit *statMean = p->tMean;

        // Data evalution
        statMean->compute();
        hist->Write();
    }

    file->Close();
    delete file;
    // Restoring working area;
    currentDir->cd();

    return;
}

void ParticleLifetime::update(const Event &ev)
{
    // adding event to all the MassMean instances
    for (Particle *p : pList)
    {
        if (p->tMean->add(ev))
        {
            static ProperTime *t = ProperTime::instance();
            double fly = t->getDecayTime();
            p->hMean->Fill(fly);
        }
    }
    return;
}