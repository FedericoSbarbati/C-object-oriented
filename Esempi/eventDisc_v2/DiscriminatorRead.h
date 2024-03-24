#ifndef DiscriminatorRead_h
#define DiscriminatorRead_h

#include "DiscriminatorBase.h"

#include <string>

class DiscriminatorRead: public virtual DiscriminatorBase {

 public:

  DiscriminatorRead();
  // deleted copy constructor and assignment to prevent unadvertent copy
  DiscriminatorRead           ( const DiscriminatorRead& x ) = delete;
  DiscriminatorRead& operator=( const DiscriminatorRead& x ) = delete;

  ~DiscriminatorRead() override;

  // read histograms for specific quantity
  void read( const std::string& name );

};

#endif

