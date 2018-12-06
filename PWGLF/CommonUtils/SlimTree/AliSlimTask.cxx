#include <iostream>

// AliROOT includes
#include "AliESDEvent.h"
#include "AliESDtrackCuts.h"
#include "AliLog.h"

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
  fEv = new SlimEvent<Double32_t>;
  fTreeEvent->Branch("Event", &fEv,32000,1);
  OpenFile(2);
  fTreeTrack = new TTree("fTreeTrack", "Track Properties");
  fTr = new SlimTrack<Double32_t>;
  fTreeTrack->Branch("Track", &fTr,32000,1);
  Post();
}

//________________________________________________________________________
void AliSlimTask::UserExec(Option_t*)
{
  AliESDEvent* esd = dynamic_cast<AliESDEvent*>(InputEvent());
  if (!esd)
    AliFatal("fESD not available");

  if (!fESDtrackCuts)
    AliFatal("fESDtrackCuts not available");

  if (!fEventCut.AcceptEvent(esd))
    return;

  fEv->Fill(fEventCut);
  fTreeEvent->Fill();
  for (Int_t i = 0; i < esd->GetNumberOfTracks(); i++) {
    fTr->Fill(esd->GetTrack(i));
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
