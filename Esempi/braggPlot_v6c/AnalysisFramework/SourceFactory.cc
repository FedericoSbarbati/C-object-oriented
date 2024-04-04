#include "AnalysisFramework/SourceFactory.h"
#include "AnalysisFramework/AnalysisInfo.h"

#include <iostream>
#include <sstream>

using namespace std;

SourceFactory::SourceFactory() {
}


SourceFactory::~SourceFactory() {
}


// create event source
EventSource* SourceFactory::create( const AnalysisInfo* info ) {
  // loop over data source builders
  static map<string,AbsFactory*>* bm = factoryMap();
  map<string,AbsFactory*>::iterator iter = bm->begin();
  map<string,AbsFactory*>::iterator iend = bm->end();
  while ( iter != iend ) {
    const pair<string,AbsFactory*>& element = *iter++;
    // create analysis object if requested
    if ( info->contains( element.first ) )
                  return element.second->create( info );
  }
  return nullptr;
}


void SourceFactory::registerFactory( const string& name, AbsFactory* f ) {
  static map<string,AbsFactory*>& fm = *factoryMap();
  fm[name] = f;
  return;
}

std::map<std::string,SourceFactory::AbsFactory*>*
                     SourceFactory::factoryMap() {
  static map<string,AbsFactory*>* fm = new map<string,AbsFactory*>;
  return fm;
}

