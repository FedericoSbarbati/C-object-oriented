#ifndef ParticleMass_h
#define ParticleMass_h

#include <vector>
#include <string>

#include "AnalysisSteering.h"
#include "TH1F.h"

class Event;
class MassMean;
class AnalysisInfo;

class ParticleMass : public AnalysisSteering
{

public:
    // Constructor
    ParticleMass(const AnalysisInfo *info);

    // Deleted copy constructor and assignment to prevent unintended copy
    ParticleMass(const ParticleMass &x) = delete;
    ParticleMass &operator=(const ParticleMass &x) = delete;

    // Destructor
    ~ParticleMass() override;

    // Function to be called at execution start
    void beginJob() override;

    // Function to be called at execution end
    void endJob() override;

    // Function to be called for each event
    void process(const Event &ev) override;

private:
    // Particle struct to hold analysis objects
    struct Particle
    {
        std::string name;
        MassMean *mMean; // Statistic object
        TH1F *hMean;     // Graph
    };

    std::vector<Particle *> pList; // List of particles

    // Function to create a "decay mode"
    void pCreate(const std::string &name, float min, float max);
};

#endif