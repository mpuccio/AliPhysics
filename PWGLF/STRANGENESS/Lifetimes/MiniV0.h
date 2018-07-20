#ifndef Lifetimes_MiniV0_h
#define Lifetimes_MiniV0_h

#include <cmath>
#include <cstdlib>
#include <limits>

#include "Utils.h"

namespace Lifetimes {

class MiniV0 {
 public:
  float GetV0radius() const { return fV0radius; }
  float GetV0pt() const { return fV0pt; }
  float GetV0eta() const { return fV0eta; }
  float GetK0sInvMass() const { return fInvMassK0s; }
  float GetLambdaInvMass() const { return fInvMassLambda; }
  float GetDistOverP() const { return fDistOverTotMom; }
  float GetV0CosPA() const;
  float GetV0chi2() const;
  float GetNegProngPvDCA() const;
  float GetPosProngPvDCA() const;
  float GetProngsDCA() const;
  float GetArmenterosAlpha() const;
  float GetArmenterosPt() const;
  unsigned char GetLeastNumberOfXedRows() const { return fLeastNxedRows; }
  float GetLeastXedRowsOverFindable() const;
  float GetMaxChi2perCluster() const;
  float GetNegProngTPCnsigmaPion() const;
  float GetNegProngTPCnsigmaProton() const;
  float GetPosProngTPCnsigmaPion() const;
  float GetPosProngTPCnsigmaProton() const;
  float GetNegProngEta() const;
  float GetPosProngEta() const;
  bool IsCowboy() const { return fChi2V0 & (1 << 7); }

  void SetV0radius(float r) { fV0radius = r; }
  void SetV0pt(float pt) { fV0pt = pt; }
  void SetV0eta(float eta) { fV0eta = eta; }
  void SetInvMasses(float k0s, float lam);
  void SetDistOverP(float distOnP) { fDistOverTotMom = distOnP; }
  void SetV0CosPA(float cospa);
  void SetV0Chi2andCowBoy(float chi2, bool cow);
  void SetProngsPvDCA(float posD, float negD);
  void SetProngsDCA(float dca);
  void SetArmenterosVariables(float alpha, float pt);
  void SetLeastNumberOfXedRows(unsigned char xedrows);
  void SetLeastXedRowsOverFindable(float ratio);
  void SetMaxChi2perCluster(float chi2);
  void SetProngsTPCnsigmas(float pPi, float pP, float nPi, float nP);
  void SetProngsEta(float posEta, float negEta);

  /// Static variables required to avoid CINT complains...
  /// To be changed with constexpr as soon as ROOT6 becomes the
  /// ALICE standard
  static const int fgkV0cosPA_n;
  static const float fgkV0cosPA_f;
  static const float fgkV0cosPA_l;
  static const float fgkV0cosPA_w;

  static const int fgkV0chi2_n;
  static const float fgkV0chi2_f;
  static const float fgkV0chi2_l;
  static const float fgkV0chi2_w;

  static const int fgkDCAProng2PV_n;
  static const float fgkDCAProng2PV_f;
  static const float fgkDCAProng2PV_l;
  static const float fgkDCAProng2PV_w;

  static const int fgkDCAProngs_n;
  static const float fgkDCAProngs_f;
  static const float fgkDCAProngs_l;
  static const float fgkDCAProngs_w;

  static const int fgkArmAlpha_n;
  static const float fgkArmAlpha_f;
  static const float fgkArmAlpha_l;
  static const float fgkArmAlpha_w;

  static const int fgkArmPt_n;
  static const float fgkArmPt_f;
  static const float fgkArmPt_l;
  static const float fgkArmPt_w;

  static const int fgkXedOverFindable_n;
  static const float fgkXedOverFindable_f;
  static const float fgkXedOverFindable_l;
  static const float fgkXedOverFindable_w;

  static const int fgkChi2xCluster_n;
  static const float fgkChi2xCluster_f;
  static const float fgkChi2xCluster_l;
  static const float fgkChi2xCluster_w;

  static const int fgkTPCsigma_n;
  static const float fgkTPCsigma_f;
  static const float fgkTPCsigma_l;
  static const float fgkTPCsigma_w;

  static const int fgkEta_n;
  static const float fgkEta_f;
  static const float fgkEta_l;
  static const float fgkEta_w;

 private:
  float fV0radius;                      // V0 decay vertex radius
  float fV0pt;                          // V0 transverse momentum
  float fV0eta;                         // V0 pseudorapidity
  float fInvMassK0s;                    // Invariant mass for K0s
  float fInvMassLambda;                 // Invariant mass for (anti-)Lambda
  float fDistOverTotMom;                // L/p
  unsigned short fV0CosPA;              // V0 cosine of pointing angle
  unsigned char fChi2V0;                // V0 fit chi2
  unsigned char fDcaNeg2PrimaryVertex;  // DCA of the negative prong to the PV
  unsigned char fDcaPos2PrimaryVertex;  // DCA of the positive prong to the PV
  unsigned char fDcaV0daughters;        // DCA between the two prongs
  unsigned char fV0armAlpha;            // Armenteros alpha
  unsigned char fV0armPt;               // Armenteros pt
  unsigned char fLeastNxedRows;         // Min number of xed roads
  unsigned char fLeastXedOverFindable;  // Min xed roads/findable clusters
  unsigned char fMaxChi2PerCluster;     // Max chi2 per cluster in TPC
  unsigned char fNsigmaPos;  // # sigma TPC pion/proton for the positive prong
  unsigned char fNsigmaNeg;  // # sigma TPC pion/proton for the negative prong
  unsigned char fEtaPos;     // Pseudorapidity of the positive prong
  unsigned char fEtaNeg;     // Pseudorapidity of the negative prong
};

inline float MiniV0::GetV0CosPA() const {
  return getBinCenter(fV0CosPA, fgkV0cosPA_w, fgkV0cosPA_f, fgkV0cosPA_l);
}
inline float MiniV0::GetV0chi2() const {
  return getBinCenter(fChi2V0 & 0x7F, fgkV0chi2_w, fgkV0chi2_f, fgkV0chi2_l);
}
inline float MiniV0::GetNegProngPvDCA() const {
  return getBinCenter(fDcaNeg2PrimaryVertex, fgkDCAProng2PV_w, fgkDCAProng2PV_f,
                      fgkDCAProng2PV_l, false, true);
}
inline float MiniV0::GetPosProngPvDCA() const {
  return getBinCenter(fDcaPos2PrimaryVertex, fgkDCAProng2PV_w, fgkDCAProng2PV_f,
                      fgkDCAProng2PV_l, false, true);
}
inline float MiniV0::GetProngsDCA() const {
  return getBinCenter(fDcaV0daughters, fgkDCAProngs_w, fgkDCAProngs_f,
                      fgkDCAProngs_l, false, true);
}
inline float MiniV0::GetArmenterosAlpha() const {
  return getBinCenter(fV0armAlpha, fgkArmAlpha_w, fgkArmAlpha_f, fgkArmAlpha_l,
                      true, true);
}
inline float MiniV0::GetArmenterosPt() const {
  return getBinCenter(fV0armPt, fgkArmPt_w, fgkArmPt_f, fgkArmPt_l, false,
                      true);
}
inline float MiniV0::GetLeastXedRowsOverFindable() const {
  return getBinCenter(fLeastXedOverFindable, fgkXedOverFindable_w,
                      fgkXedOverFindable_f, fgkXedOverFindable_l);
}
inline float MiniV0::GetMaxChi2perCluster() const {
  return getBinCenter(fMaxChi2PerCluster, fgkChi2xCluster_w, fgkChi2xCluster_f,
                      fgkChi2xCluster_l, false, true);
}

inline float MiniV0::GetNegProngEta() const {
  return getBinCenter(fEtaNeg, fgkEta_w, fgkEta_f, fgkEta_l, true, true);
}
inline float MiniV0::GetPosProngEta() const {
  return getBinCenter(fEtaPos, fgkEta_w, fgkEta_f, fgkEta_l, true, true);
}

inline float MiniV0::GetNegProngTPCnsigmaPion() const {
  return getBinCenter((fNsigmaNeg & 0xF0) >> 4, fgkTPCsigma_w, fgkTPCsigma_f,
                      fgkTPCsigma_l, false, true);
}
inline float MiniV0::GetNegProngTPCnsigmaProton() const {
  return getBinCenter((fNsigmaNeg & 0x0F), fgkTPCsigma_w, fgkTPCsigma_f,
                      fgkTPCsigma_l, false, true);
}
inline float MiniV0::GetPosProngTPCnsigmaPion() const {
  return getBinCenter((fNsigmaPos & 0xF0) >> 4, fgkTPCsigma_w, fgkTPCsigma_f,
                      fgkTPCsigma_l, false, true);
}
inline float MiniV0::GetPosProngTPCnsigmaProton() const {
  return getBinCenter((fNsigmaPos & 0x0F), fgkTPCsigma_w, fgkTPCsigma_f,
                      fgkTPCsigma_l, false, true);
}

inline void MiniV0::SetInvMasses(float k0s, float lam) {
  fInvMassK0s = k0s;
  fInvMassLambda = lam;
}

inline void MiniV0::SetV0CosPA(float cospa) {
  fV0CosPA = getBinnedValue<unsigned short>(cospa, fgkV0cosPA_w, fgkV0cosPA_f,
                                            fgkV0cosPA_l);
}

inline void MiniV0::SetV0Chi2andCowBoy(float chi2, bool cow) {
  fChi2V0 = getBinnedValue<char>(chi2, fgkV0chi2_w, fgkV0chi2_l);
  if (cow) fChi2V0 += 1 << 7;
}

inline void MiniV0::SetProngsPvDCA(float posD, float negD) {
  fDcaPos2PrimaryVertex =
      getBinnedValue<unsigned char>(posD, fgkDCAProng2PV_w, fgkDCAProng2PV_l);
  fDcaNeg2PrimaryVertex =
      getBinnedValue<unsigned char>(negD, fgkDCAProng2PV_w, fgkDCAProng2PV_l);
}

inline void MiniV0::SetProngsDCA(float dca) {
  fDcaV0daughters =
      getBinnedValue<unsigned char>(dca, fgkDCAProngs_w, fgkDCAProngs_l);
}

inline void MiniV0::SetArmenterosVariables(float alpha, float pt) {
  fV0armAlpha = getBinnedValue<unsigned char>(alpha, fgkArmAlpha_w,
                                              fgkArmAlpha_f, fgkArmAlpha_l);
  fV0armPt = getBinnedValue<unsigned char>(pt, fgkArmPt_w, fgkArmPt_l);
}

inline void MiniV0::SetLeastNumberOfXedRows(unsigned char xedrows) {
  fLeastNxedRows = xedrows;
}

inline void MiniV0::SetLeastXedRowsOverFindable(float ratio) {
  fLeastXedOverFindable =
      getBinnedValue<unsigned char>(ratio, fgkXedOverFindable_w, fgkXedOverFindable_l);
}

inline void MiniV0::SetMaxChi2perCluster(float chi2) {
  fMaxChi2PerCluster = getBinnedValue<unsigned char>(chi2, fgkChi2xCluster_w);
}

inline void MiniV0::SetProngsTPCnsigmas(float pPi, float pP, float nPi,
                                        float nP) {
  fNsigmaNeg = (std::abs(nP) > fgkTPCsigma_l)
                   ? 0x0F
                   : getBinnedValue<unsigned char>(std::abs(nP), fgkTPCsigma_w);
  fNsigmaNeg +=
      ((std::abs(nPi) > fgkTPCsigma_l)
           ? 0x0F
           : getBinnedValue<unsigned char>(std::abs(nPi), fgkTPCsigma_w))
      << 4;
  fNsigmaPos = (std::abs(pP) > fgkTPCsigma_l)
                   ? 0x0F
                   : getBinnedValue<unsigned char>(std::abs(pP), fgkTPCsigma_w);
  fNsigmaPos +=
      ((std::abs(pPi) > fgkTPCsigma_l)
           ? 0x0F
           : getBinnedValue<unsigned char>(std::abs(pPi), fgkTPCsigma_w))
      << 4;
}

inline void MiniV0::SetProngsEta(float posEta, float negEta) {
  fEtaNeg = getBinnedValue<unsigned char>(negEta, fgkEta_w, fgkEta_f, fgkEta_l);
  fEtaPos = getBinnedValue<unsigned char>(posEta, fgkEta_w, fgkEta_f, fgkEta_l);
}

}  // namespace Lifetimes

#endif
