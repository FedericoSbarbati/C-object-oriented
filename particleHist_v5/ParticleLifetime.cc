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
    // assign "time" as name for this analyzer and factory
    ParticleLifetimeFactory() : AnalysisFactory::AbsFactory("time") {}
    // create a ParticleLifeTime when builder is run
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

void ParticleLifetime::pCreate(const string &name,
                               double minMass, double maxMass,
                               double minTime, double maxTime,
                               double minScan, double maxScan,
                               double scanStep)
{
    // create name for TH1F object
    string label = " decay time hist; T[ns]; Occurrences";
    string title = name + label;
    string mane = name + "TIME";
    const char *hName = mane.c_str();
    const char *hTitle = title.c_str();

    // Setting bin number constant
    int nBins = 150;

    // create TH1F and statistic objects and store their pointers
    Particle *p = new Particle;
    p->name = name;
    p->tMean = new LifetimeFit(minMass, maxMass,
                               minTime, maxTime,
                               minScan, maxScan,
                               scanStep);
    p->hMean = new TH1F(hName, hTitle, nBins, minTime, maxTime);
    p->hMean->SetFillColor(kRed);
    pList.push_back(p);

    return;
}

void ParticleLifetime::beginJob()
{
    pList.reserve(10);

    // Opening file with fitting informations
    ifstream file(aInfo->value("fit").c_str());
    if (!file.is_open())
    {
        cerr << "Error opening file with name: " << aInfo->value("ranges") << endl;
        return;
    }
    string name;
    double minMass;
    double maxMass;
    double minTime;
    double maxTime;
    double minScan;
    double maxScan;
    double scanStep;
    while (file >> name >> minMass >> maxMass >> minTime >> maxTime >> minScan >> maxScan >> scanStep)
    {
        // creating Particles instances
        pCreate(name,
                minMass, maxMass,
                minTime, maxTime,
                minScan, maxScan, scanStep);
    }
    file.close();

    return;
}

void ParticleLifetime::endJob()
{
    // save current working area
    TDirectory *currentDir = gDirectory;
    // open histogram file
    TFileProxy *file = new TFileProxy(aInfo->value("time").c_str(), "RECREATE");
    if (!file)
    {
        cerr << "Error opening file with name: " << aInfo->value("time") << endl;
        delete file;
        return;
    }

    // loop over ParticleLifetime::Particle objects
    for (ParticleLifetime::Particle *p : pList)
    {
        TH1F *hist = p->hMean;
        LifetimeFit *statMean = p->tMean;

        // Data evalution
        statMean->compute();

        // Printing results
        cout << endl;
        cout << "For particle: " << p->name << endl;
        cout << "Mean lifetime: " << statMean->getLifeTime() << " +/- " << statMean->getLifeTimeError() << endl;
        cout << "N accepted events: " << p->tMean->getNacceptedEv() << endl;
        cout << endl;

        // Writing histogram
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
    // adding event to the lifetime fit
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