#ifndef Task_HH
#define Task_HH

#include <TTree.h>
#include <TChain.h>

#include "AliEventCuts.h"
#include "AliAnalysisTaskSE.h"

#include "SlimEvent.h"
#include "SlimTrack.h"

class AliSlimTask : public AliAnalysisTaskSE {
  public:
  //Constructors and destructor
  AliSlimTask();
  virtual ~AliSlimTask();

  //Standard AnalysisTask functions
  virtual void UserCreateOutputObjects();
  virtual void UserExec(Option_t* option);
  virtual void Terminate(Option_t*);

  //Standard track and event cuts
  AliEventCuts fEventCut;         //!<! basic cut variables for events
  AliESDtrackCuts* fESDtrackCuts; /// basic cut variables

  private:
  TTree* fTreeEvent; //!<! TTree to store information of the single event
  SlimEvent<Double32_t> fEv;
  TTree* fTreeTrack; //!<! TTree to store information of the single track
  SlimTrack<Double32_t> fTr;

  //
  AliSlimTask(const AliSlimTask&);            //! Copy constructor
  AliSlimTask& operator=(const AliSlimTask&); //! Not implemented
  void DefineIO()
  {
    DefineInput(0, TChain::Class());
    DefineOutput(1, TTree::Class());
    DefineOutput(2, TTree::Class());
  };

  void Post()
  {
    PostData(1, fTreeEvent);
    PostData(2, fTreeTrack);
  };

  ClassDef(AliSlimTask, 1); //AliSlimTask used for AOD/ESD filtering
};

#endif
