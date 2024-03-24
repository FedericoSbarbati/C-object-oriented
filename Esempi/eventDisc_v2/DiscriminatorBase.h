#ifndef DiscriminatorBase_h
#define DiscriminatorBase_h

#include <string>
#include <map>

class TH1F;

class DiscriminatorBase
{

public:
  DiscriminatorBase();
  // deleted copy constructor and assignment to prevent unadvertent copy
  DiscriminatorBase(const DiscriminatorBase &x) = delete;
  DiscriminatorBase &operator=(const DiscriminatorBase &x) = delete;

  virtual ~DiscriminatorBase();

  // activate or deactivate use of a specific quantity
  void setVariable(const std::string &name, bool active);
  // compute discriminating variable for the full set of quantities
  float get() const;

protected:
  // accept variables from derived classes
  void registerVariable(const std::string &name,
                        const float *content, bool active = true);
  // information for each specific quantity
  struct VarDescription
  {
    const float *content;
    TH1F *sigHisto;
    TH1F *bkgHisto;
    bool use;
  };
  // access quantity information map
  std::map<std::string, VarDescription *>::const_iterator begin();
  std::map<std::string, VarDescription *>::const_iterator find(const std::string &name);
  std::map<std::string, VarDescription *>::const_iterator end();

private:
  // compute probabilities for a variable
  static void get(float x, float &dSig,
                  TH1F *hSig, TH1F *hBkg);

  // quantity information map
  std::map<std::string, VarDescription *> varMap;
};

#endif
