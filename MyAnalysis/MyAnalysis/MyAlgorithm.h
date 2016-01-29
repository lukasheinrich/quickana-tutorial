#ifndef MyAnalysis_MyAlgorithm_H
#define MyAnalysis_MyAlgorithm_H

#include <EventLoop/Algorithm.h>

#include <QuickAna/Configuration.h>
#include <QuickAna/QuickAna.h>
#include <memory>

class MyAlgorithm : public EL::Algorithm, public ana::Configuration

{
  // put your configuration variables here as public variables.
  // that way they can be set directly from CINT and python.
public:
  // float cutValue;



  // variables that don't get filled at submission time should be
  // protected from being send from the submission node to the worker
  // node (done by the //!)
public:
  // Tree *myTree; //!
  // TH1 *myHist; //!



  // this is a standard constructor
  MyAlgorithm ();

  // these are the functions inherited from Algorithm
  virtual EL::StatusCode setupJob (EL::Job& job);
  virtual EL::StatusCode fileExecute ();
  virtual EL::StatusCode histInitialize ();
  virtual EL::StatusCode changeInput (bool firstFile);
  virtual EL::StatusCode initialize ();
  virtual EL::StatusCode execute ();
  virtual EL::StatusCode postExecute ();
  virtual EL::StatusCode finalize ();
  virtual EL::StatusCode histFinalize ();

private:
  // the quickAna tool.
  // the unique_ptr is used to ensure the tool gets destroyed and recreated
  // when running over multiple samples
  // the //! is important to indicate that the tool is not going to be streamed
  std::unique_ptr<ana::IQuickAna> quickAna; //!
  
  // this is needed to distribute the algorithm to the workers
  ClassDef(MyAlgorithm, 1);
};

#endif
