// Copyright CERN. This software is distributed under the terms of the GNU
// General Public License v3 (GPL Version 3).
//
// See http://www.gnu.org/licenses/ for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

/// \file AliONNXInterface.cxx
/// \author fabio.catalano@cern.ch

#include "AliONNXInterface.h"
#include <type_traits>


AliONNXInterface::AliONNXInterface(std::string name, bool debug) :
  fInterfaceName{name},
  fEnv{std::nullptr_t}
{
  OrtLoggingLevel log_level;
  const char* env_name;
  if(debug) {
    log_level = ORT_LOGGING_LEVEL_VERBOSE;
    env_name = "debug";
  }
  else {
    log_level = ORT_LOGGING_LEVEL_WARNING;
    env_name = fInterfaceName.c_str();
  }
  fEnv = Ort::Env(log_level, env_name);
}

bool AliONNXInterface::LoadXGBoostModel(std::string path) {

  return false;
}

float AliONNXInterface::Predict(float *fearures, int size) {

  return 0.f;
}