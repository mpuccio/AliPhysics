#ifndef ALIANALYSISTASKNanoAODFILTERSELECTION_H
#define ALIANALYSISTASKNanoAODFILTERSELECTION_H

#include "AliPhysicsSelection.h"
#include "AliAnalysisTaskSE.h"
#include "AliPID.h"
#include "AliEventCuts.h"

class AliESDtrackCuts;

/// The NanoAOD selection perform an offline triggering using a combination of event selection
/// and PID triggering on the tracks. If the trigger conditions are not satisfied, then the
/// following tasks are not executed
class AliAnalysisTaskNanoAODFilterSelection : public AliAnalysisTaskSE {
public:
  AliAnalysisTaskNanoAODFilterSelection() : AliAnalysisTaskSE("NanoAODFilterSelection") {}
  AliAnalysisTaskNanoAODFilterSelection(std::string taskName);

  virtual void UserExec(Option_t* /*option*/);
  void TriggerOnSpecies(AliPID::EParticleType sp, AliESDtrackCuts* cuts, double nsigmaTPC, double ptRangeTPC[2], double nsigmaTOF, double ptRangeTOF[2]);

  static AliAnalysisTaskNanoAODFilterSelection* AddTask(std::string name = "NanoAODFilterSelection");

  AliEventCuts fEventCuts;

private:
  AliESDtrackCuts* fTrackCuts[AliPID::kSPECIESC];
  double fTOFpidTriggerNsigma[AliPID::kSPECIESC];   
  double fTOFpidTriggerPtRange[AliPID::kSPECIESC][2];
  double fTPCpidTriggerNsigma[AliPID::kSPECIESC];
  double fTPCpidTriggerPtRange[AliPID::kSPECIESC][2];

  ClassDef(AliAnalysisTaskNanoAODFilterSelection,1);
};

#endif