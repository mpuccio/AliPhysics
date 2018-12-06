
// ROOT includes
#include "TChain.h"
#include "TTree.h"
#include <iostream>

// AliROOT includes
#include "AliESDEvent.h"
#include "AliESDtrackCuts.h"
#include "AliEventCuts.h"

// Custom includes
#include "SlimEvent.h"
#include "SlimTrack.h"

#include "AliSlimTask.h"

ClassImp(AliSlimTask);

//________________________________________________________________________
AliSlimTask::AliSlimTask()
    : AliAnalysisTaskSE("AliSlimTask")
    , fEventCut()
    , fESDtrackCuts()
    , fTreeEvent()
    , fEv()
    , fTreeTrack()
    , fTr()
{
  DefineIO();
}

//________________________________________________________________________
AliSlimTask::AliSlimTask(const AliSlimTask& copy)
    : AliSlimTask()
{
}

//________________________________________________________________________
AliSlimTask::~AliSlimTask()
{
}

//________________________________________________________________________
void AliSlimTask::UserCreateOutputObjects()
{
  fESDtrackCuts = (AliESDtrackCuts*)AliESDtrackCuts::GetStandardITSTPCTrackCuts2011(kTRUE, 1);
  OpenFile(1);
  fTreeEvent = new TTree("fTreeEvent", "Event Properties");
  fTreeEvent->Branch("Event", &fEv);
  OpenFile(2);
  fTreeTrack = new TTree("fTreeTrack", "Track Properties");
  fTreeTrack->Branch("Track", &fTr);
  Post();
}

//________________________________________________________________________
void AliSlimTask::UserExec(Option_t*)
{
  AliESDEvent* esd = dynamic_cast<AliESDEvent*>(InputEvent());
  if (!esd) {
    AliError("fESD not available");
    // Post output data.
    Post();
    return;
  }
  if (!fESDtrackCuts) {
    AliError("fESDtrackCuts not available");
    // Post output data.
    Post();
    return;
  }
  fEv.Fill(fEventCut);
  fTreeEvent->Fill();
  for (Int_t i = 0; i < esd->GetNumberOfTracks(); i++) {
    fTr.Fill(esd->GetTrack(i));
    fTreeTrack->Fill();
  }
  fTreeTrack->FlushBaskets();
  Post();
}

//________________________________________________________________________
void AliSlimTask::Terminate(Option_t*)
{
  return;
}
