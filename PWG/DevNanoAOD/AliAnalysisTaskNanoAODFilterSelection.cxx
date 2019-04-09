#include "AliAnalysisTaskNanoAODFilterSelection.h"
#include <AliVEvent.h>
#include <AliAnalysisManager.h>
#include <AliESDtrackCuts.h>
#include <AliInputEventHandler.h>
#include <AliPIDResponse.h>
#include <TChain.h>

#include <algorithm>
#include <cmath>
#include <iostream>

AliAnalysisTaskNanoAODFilterSelection::AliAnalysisTaskNanoAODFilterSelection(std::string taskName) : AliAnalysisTaskSE{taskName.data()},
  fEventCuts{},
  fTrackCuts{},
  fTOFpidTriggerNsigma{},   
  fTOFpidTriggerPtRange{},
  fTPCpidTriggerNsigma{},
  fTPCpidTriggerPtRange{}
{
  for (int iSpecies{0}; iSpecies < AliPID::kSPECIESC; ++iSpecies) {
    fTrackCuts[iSpecies] = nullptr;
    fTOFpidTriggerNsigma[iSpecies] = -1.;
    fTOFpidTriggerPtRange[iSpecies][0] = 0.;
    fTOFpidTriggerPtRange[iSpecies][1] = 1000.;
    fTPCpidTriggerNsigma[iSpecies] = -1.;
    fTPCpidTriggerPtRange[iSpecies][0] = 0.;
    fTPCpidTriggerPtRange[iSpecies][1] = 1000.;
  }
  DefineInput(0, TChain::Class());  
}


void AliAnalysisTaskNanoAODFilterSelection::TriggerOnSpecies(AliPID::EParticleType sp, AliESDtrackCuts* cuts, double nsigmaTPC, double ptRangeTPC[2], double nsigmaTOF, double ptRangeTOF[2]) {
  fTrackCuts[sp] = cuts;
  fTOFpidTriggerNsigma[sp] = nsigmaTOF;
  fTOFpidTriggerPtRange[sp][0] = ptRangeTOF[0];
  fTOFpidTriggerPtRange[sp][1] = ptRangeTOF[1];
  fTPCpidTriggerNsigma[sp] = nsigmaTPC;
  fTPCpidTriggerPtRange[sp][0] = ptRangeTPC[0];
  fTPCpidTriggerPtRange[sp][1] = ptRangeTPC[1];
}

void AliAnalysisTaskNanoAODFilterSelection::UserExec(Option_t* /*option*/) {
  AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
  AliInputEventHandler* handl = (AliInputEventHandler*)mgr->GetInputEventHandler();
  AliVEvent *ev = InputEvent();
  AliPIDResponse* pid = handl->GetPIDResponse();

  bool acceptEvent = fEventCuts.AcceptEvent(ev);

  bool loopOnTracks{std::any_of(fTrackCuts, fTrackCuts+AliPID::kSPECIESC, [](AliESDtrackCuts* cut) { return cut != nullptr; } )};
  if (loopOnTracks && acceptEvent) {
    acceptEvent = false;
    
    const int nTracks = ev->GetNumberOfTracks();
    for (int it = 0; it < nTracks && !acceptEvent; it++) {
      AliVTrack* trk = (AliVTrack*)ev->GetTrack(it);
      for (int iSpecies{0}; iSpecies < AliPID::kSPECIESC && !acceptEvent; ++iSpecies) {
        if (!fTrackCuts[iSpecies] && fTPCpidTriggerNsigma[iSpecies] < 0. && fTOFpidTriggerNsigma[iSpecies] < 0.)
          continue;

        if (fTrackCuts[iSpecies])
          if (!fTrackCuts[iSpecies]->AcceptVTrack(trk))
            continue;

        double pt = trk->Pt() * AliPID::ParticleCharge(iSpecies);
        double nTPCsigma = std::abs(pid->NumberOfSigmasTPC(trk,AliPID::EParticleType(iSpecies)));
        double nTOFsigma = std::abs(pid->NumberOfSigmasTOF(trk,AliPID::EParticleType(iSpecies)));
        if ((nTPCsigma < fTPCpidTriggerNsigma[iSpecies] && pt > fTPCpidTriggerPtRange[iSpecies][0] && pt < fTPCpidTriggerPtRange[iSpecies][1]) ||
            (nTOFsigma < fTOFpidTriggerNsigma[iSpecies] && nTPCsigma < fTPCpidTriggerNsigma[iSpecies] && pt > fTOFpidTriggerPtRange[iSpecies][0] && pt < fTOFpidTriggerPtRange[iSpecies][1])) {
          acceptEvent = true;
        }
      }
    }
  }
  if (!acceptEvent)
    mgr->BreakExecutionChain();
}


AliAnalysisTaskNanoAODFilterSelection* AliAnalysisTaskNanoAODFilterSelection::AddTask(std::string name) {
  AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
  if (!mgr) {
    ::Error("AddTaskPhysicsSelection", "No analysis manager to connect to.");
    return nullptr;
  }

  if (!mgr->GetInputEventHandler()) {
    ::Error("AddTaskPhysicsSelection", "This task requires an input event handler");
    return nullptr;
  }

  AliAnalysisTaskNanoAODFilterSelection *task = new AliAnalysisTaskNanoAODFilterSelection(name);
  mgr->AddTask(task);

  mgr->ConnectInput(task, 0, mgr->GetCommonInputContainer());

  return task;
}