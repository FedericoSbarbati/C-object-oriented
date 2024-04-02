#ifndef ParticleMass_h
#define ParticleMass_h

#include <vector>
#include <string>

#include "AnalysisSteering.h"
#include "util/include/ActiveObserver.h"
#include "TH1F.h"

class Event;
class MassMean;
class AnalysisInfo;

class ParticleMass : public AnalysisSteering,
                     public ActiveObserver<Event>
{

public:
    ParticleMass(const AnalysisInfo *info);
    // deleted copy constructor and assignment to prevent unadvertent copy
    ParticleMass(const ParticleMass &x) = delete;
    ParticleMass &operator=(const ParticleMass &x) = delete;

    ~ParticleMass() override;

    // function to be called at execution start
    void beginJob() override;

    // function to be called at execution end
    void endJob() override;

    // function to be called for each event
    void update(const Event &ev) override;

private:
    // Particle struct to hold analysis objects
    struct Particle
    {
        std::string name;
        MassMean *mMean; // statistic object
        TH1F *hMean;     // graph
    };
    std::vector<Particle *> pList;
    // function to create a "decay mode"
    void pCreate(const std::string &name, float min, float max);
};

#endif