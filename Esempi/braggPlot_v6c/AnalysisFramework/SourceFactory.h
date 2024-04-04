#ifndef SourceFactory_h
#define SourceFactory_h

#include <string>
#include <map>

class EventSource;
class AnalysisInfo;

class SourceFactory {

 public:

  SourceFactory();
  // deleted copy constructor and assignment to prevent unadvertent copy
  SourceFactory           ( const SourceFactory& x ) = delete;
  SourceFactory& operator=( const SourceFactory& x ) = delete;

  virtual ~SourceFactory();

  // create event source
  static EventSource* create( const AnalysisInfo* info );

  // event source abstract factory
  class AbsFactory {
   public:
    AbsFactory( const std::string& name ) { registerFactory( name, this ); }
    virtual ~AbsFactory() {}
    virtual EventSource* create( const AnalysisInfo* info ) = 0;
  };

 private:

  // function to add analyzer concrete factories
  static void registerFactory( const std::string& name, AbsFactory* f );
  // map to associate analyzer names with corresponding factories
  static std::map<std::string,AbsFactory*>* factoryMap();

};

#endif

