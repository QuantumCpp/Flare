#pragma once
#include "../EnumsClass/ValidationError.h"
#include "../GeneralLibraries/GeneralLibraries.h"
#include <functional>

struct DataErrorDetail{
  ValidationError ErrorID;
  std::string NameError;
  std::string ShortDetail;

  std::function<void(const DataErrorDetail*)> handler;
};



