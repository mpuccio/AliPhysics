AlidNdPtUnifiedAnalysisTask* AddTask_eperezle_Unified(Int_t cutModeLow = 100, Int_t cutModeHigh = 101)
{

    AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();

    if (!mgr) {
        Error("AddTask_eperezle_Unified", "No analysis manager found.");
        return 0;
    }

    // Switch off all AliInfo (too much output!!!)
    AliLog::SetGlobalLogLevel(AliLog::kError);
    mgr->SetDebugLevel(0);


    TString type = mgr->GetInputEventHandler()->GetDataType(); // can be "ESD" or "AOD"
    Bool_t hasMC=(AliAnalysisManager::GetAnalysisManager()->GetMCtruthEventHandler()!=0x0);

   //AliESDtrackCuts* esdTrackCuts = new AliESDtrackCuts("AliESDtrackCuts");

  char taskName[100] = "";


  for(Int_t cutMode = cutModeLow; cutMode < cutModeHigh; cutMode++){
    sprintf(taskName, "dNdPt_cutMode_%d", cutMode);

    AlidNdPtUnifiedAnalysisTask *task = new AlidNdPtUnifiedAnalysisTask("AlidNdPtUnifiedAnalysisTask_eperezle");
    task->SetUseMC(hasMC);
    if(type.Contains("ESD")) task->SetUseESD();
    else task->SetUseAOD();
    task->SetUseMultiplicity(kTRUE);
    task->SelectCollisionCandidates(AliVEvent::kINT7);
    task->SetTriggerMask(AliVEvent::kINT7 ); //kINT7


    const Int_t multNbins =200;
    Double_t binsMult[multNbins+1];
    for (Int_t ii = 0; ii<=multNbins;ii++){binsMult[ii]=5*ii-0.5;}
    task->SetBinsMultCent(multNbins,binsMult);

    // change pt binning
    const Int_t ptNbins = 81;
    Double_t bins[82] = {0.0, 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.2, 3.4, 3.6, 3.8, 4.0, 4.5, 5.0, 5.5, 6.0, 6.5, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 18.0, 20.0, 22.0, 24.0, 26.0, 28.0, 30.0, 32.0, 34.0, 36.0, 40.0, 45.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0, 110.0, 120.0, 130.0, 140.0, 150.0, 160.0, 180.0, 200.0};
    Double_t* binsPt = new Double_t[82];
    for (int i=0; i<82; i++) {binsPt[i] = bins[i];}
    task->SetBinsPt(ptNbins, binsPt);


    Int_t nBinsCent = 1;
    Double_t centBinEdgesDummy[2] = {0., 100.};
    Double_t centBinEdgesUsed[9] = {0., 5., 10., 20., 40., 60., 80., 90., 100.};
    Double_t* centBinEdges = centBinEdgesDummy;

    task->SetBinsCent(nBinsCent, centBinEdges);


    /// Acceptance cuts for tracks

    task->SetMinEta(-1.);
    task->SetMaxEta(1.);
    task->SetMinPt(0.10);

    task->Set2013pA(kFALSE);
    task->Set2015data(kTRUE);

    ///TOF pileup, kTRUE only for Matching efficiency studies
    task->SetTOFbunchCrossing(kFALSE);

    task->SetMeanXYZv(0.0,0.0,0.0);
    task->SetSigmaMeanXYZv(1.0,1.0,10.0);
    task->SetZvtx(30.);
    task->SetEventTriggerRequired(kTRUE);

    // Quality cuts for tracks

    // TPC
    task->SetTPCRefit(kTRUE);
    task->SetRatioCrossedRowsOverFindableClustersTPC(0.8);
    task->SetMaxchi2perTPCclu(4.);
    task->SetFractionSharedClustersTPC(0.4);

    // ITS
    task->SetITSRefit(kTRUE);
    task->SetClusterReqITS(kTRUE);
    task->SetMaxchi2perITSclu(36.);

    // primary selection
    task->SetSigmaToVertex(kFALSE);
    task->SetDCAtoVertexZ(2.0);
    task->SetDCAtoVertexXYPtDep("0.0182+0.0350/pt^1.01");
    task->SetKinkDaughters(kFALSE);
    task->SetDCAtoVertex2D(kFALSE);
    task->SetMaxChi2TPCConstrained(36.);
    task->SetMinLenghtInActiveZoneTPC(0);
    task->SetGeometricalCut(kTRUE,3,130,1.5,0.85,0.7); ///if kTRUE comment CrossedRowsTPC cut
    //task->SetMinCrossedRowsTPC(120);


    //Switch Low/High to study systematics uncertanties
    if(cutMode==101){task->SetDCAtoVertexZ(1.0); }
    if(cutMode==102){task->SetDCAtoVertexZ(5.0); }

    if(cutMode==103){task->SetDCAtoVertexXYPtDep("0.0104+0.0200/pt^1.01");}
    if(cutMode==104){task->SetDCAtoVertexXYPtDep("0.0260+0.0500/pt^1.01");}

    if(cutMode==105){task->SetRatioCrossedRowsOverFindableClustersTPC(0.7);}
    if(cutMode==106){task->SetRatioCrossedRowsOverFindableClustersTPC(0.9);}

    if(cutMode==107){task->SetFractionSharedClustersTPC(0.2);}
    if(cutMode==108){task->SetFractionSharedClustersTPC(1.0);}

    if(cutMode==109){task->SetMaxchi2perTPCclu(3); }
    if(cutMode==110){task->SetMaxchi2perTPCclu(5); }

    if(cutMode==111){task->SetMaxchi2perITSclu(25.); }
    if(cutMode==112){task->SetMaxchi2perITSclu(49.); }

    if(cutMode==113){task->SetClusterReqITS(kFALSE);}

    if(cutMode==114){task->SetGeometricalCut(kTRUE,4,130,1.5,0.85,0.7); }
    if(cutMode==115){task->SetGeometricalCut(kTRUE,2,130,1.5,0.85,0.7); }

    if(cutMode==116){task->SetGeometricalCut(kTRUE,3,140,1.5,0.85,0.7); }
    if(cutMode==117){task->SetGeometricalCut(kTRUE,3,120,1.5,0.85,0.7); }

    if(cutMode==118){task->SetMaxChi2TPCConstrained(25.); }
    if(cutMode==119){task->SetMaxChi2TPCConstrained(49.); }

    //event cuts study
    if(cutMode == 120) {task->SetZvtx(5.);}
    if(cutMode == 121) {task->SetZvtx(20.);}



    //Matching Efficiency
    if(cutMode==200)
    {
    // Calculate matching efficiency: TPC only with Crossed Rows
    task->SetTPCRefit(kTRUE);
    task->SetDCAtoVertexZ(3.2);
    task->SetDCAtoVertexXY(2.4);
    task->SetGeometricalCut(kTRUE,3,130,1.5,0.85,0.7);
    task->SetRatioCrossedRowsOverFindableClustersTPC(0.8);
    task->SetFractionSharedClustersTPC(0.4);
    task->SetMaxchi2perTPCclu(4.0);

    task->SetITSRefit(kFALSE);
    task->SetClusterReqITS(kFALSE);

    //Calculate matching efficiency: TPC + ITS with Crossed Rows
    if (cutMode==201){
         task->SetITSRefit(kTRUE);
         task->SetClusterReqITS(kTRUE);
       }

   //Calculate matching efficiency: TPC + ITS without SPD hit with Crossed Rows
      if (cutMode==202){
         task->SetITSRefit(kTRUE);
         task->SetClusterReqITS(kFALSE);
        }
    }


    mgr->AddTask(task);

    AliAnalysisDataContainer *cinput = mgr->GetCommonInputContainer();
    AliAnalysisDataContainer *coutput = mgr->CreateContainer(taskName,
            TList::Class(),
            AliAnalysisManager::kOutputContainer,
            "AnalysisResults.root");



    mgr->ConnectInput(task, 0, cinput);
    mgr->ConnectOutput(task, 1, coutput);

    }

    return task;
}
