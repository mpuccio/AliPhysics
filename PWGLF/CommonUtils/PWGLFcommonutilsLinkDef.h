#ifdef __CINT__

#pragma link C++ class AliAnalysisTaskSimSpectraLF+;


#endif

#ifdef __CLING__

#pragma link C++ class AliSlimTask+;
#pragma link C++ class SlimEvent<float>+;
#pragma link C++ class SlimTrack<float>+;
#pragma link C++ class std::vector<SlimTrack<float>>+;
#pragma link C++ class SlimEvent<Double32_t>+;
#pragma link C++ class SlimTrack<Double32_t>+;
#pragma link C++ class std::vector<SlimTrack<Double32_t>>+;

#endif
