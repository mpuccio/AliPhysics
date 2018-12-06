#ifndef SLIMTREE_EVENT
#define SLIMTREE_EVENT

#include <AliEventCuts.h>
#include <AliVVertex.h>

#include <Rtypes.h>
#include <type_traits>

template<typename F>
struct SlimEvent {
  static_assert(std::is_floating_point<F>::value, "SlimEvent wants a floating point type.");

  F VtxX = -999;
  F VtxY = -999;
  F VtxZ = -999;
  F Multiplicity = -999; //[-1, 16383, 14]

  void Fill(AliEventCuts &ev) {
    const AliVVertex* vtx = ev.GetPrimaryVertex();
    VtxX = vtx->GetX();
    VtxY = vtx->GetY();
    VtxZ = vtx->GetZ();
  };

  ClassDefInlineNV(SlimEvent<F>, 1)

};

#endif
