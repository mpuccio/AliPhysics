#if !defined(__CINT__) || defined(__MAKECINT__)
#include "AliAnalysisDataContainer.h"
#include "TChain.h"
#include "TTree.h"
#include <AliAnalysisManager.h>
#include <AliMCEventHandler.h>
#include <iostream>

#include "AliESDEvent.h"
#include "AliESDtrackCuts.h"
#include "AliEventCuts.h"

#include <AliSlimTask.h>
#endif

AliSlimTask* AddTask(const Bool_t isMC)
{
  AliAnalysisManager* mgr = AliAnalysisManager::GetAnalysisManager();
  if (!mgr) {
    Error("AddTask", "No analysis manager to connect to.");
    return NULL;
  }

  // Check the analysis type using the event handlers connected to the analysis manager.
  //==============================================================================
  if (!mgr->GetInputEventHandler()) {
    Error("AddTask", "This task requires an input event handler");
    return NULL;
  }

  TString type = mgr->GetInputEventHandler()->GetDataType(); // can be "ESD" or "AOD"

  // Add MC handler (for kinematics)
  if (isMC) {
    AliMCEventHandler* handler = new AliMCEventHandler;
    handler->SetReadTR(kFALSE);
    mgr->SetMCtruthEventHandler(handler);
  }

  // Create and configure the task
  AliSlimTask* task = new AliSlimTask();
  mgr->AddTask(task);

  // Create ONLY the output containers for the data produced by the task.
  // Get and connect other common input/output containers via the manager as below
  //==============================================================================
  //   TString outputFileName = AliAnalysisManager::GetCommonFileName();
  //   outputFileName += ":PWGLFSpectraTOF";
  //   Info("AddTask","The results of this task will be found in: %s",outputFileName.Data());

  //Create and attach input
  Int_t nc = 0;
  mgr->ConnectInput(task, nc++, mgr->GetCommonInputContainer());

  //Create and attach output
  {
    AliAnalysisDataContainer* cOutput = mgr->CreateContainer("fTreeEvent", TTree::Class(), AliAnalysisManager::kOutputContainer, "TreeEvent.root");
    cOutput->SetSpecialOutput();
    mgr->ConnectOutput(task, nc++, cOutput);
  }
  {
    AliAnalysisDataContainer* cOutput = mgr->CreateContainer("fTreeTrack", TTree::Class(), AliAnalysisManager::kOutputContainer, "TreeTrack.root");
    cOutput->SetSpecialOutput();
    mgr->ConnectOutput(task, nc++, cOutput);
  }
  return task;
}
