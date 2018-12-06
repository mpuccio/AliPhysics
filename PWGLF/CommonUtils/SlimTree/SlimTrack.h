#ifndef SLIMTREE_TRACK
#define SLIMTREE_TRACK

#include <AliVTrack.h>

#include <Rtypes.h>
#include <type_traits>

template<typename F>
struct SlimTrack {
  static_assert(std::is_floating_point<F>::value, "SlimTrack wants a floating point type.");

  F Pt = -999;
  F Eta = -999;
  F Phi = -999;

  void Fill(AliVSlimTrack *track) {
    Pt = track->Pt();
    Eta = track->Eta();
    Phi = track->Phi();
  };

  ClassDefInlineNV(SlimTrack<F>, 1)
};

#endif
