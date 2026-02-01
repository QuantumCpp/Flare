#pragma once
#include <functional>
#include <string> 
#include "ValidationError.h"

struct DataErrorDetail{
  ValidationError ErrorID;
  std::string NameError;
  std::string ShortDetail;

  std::function<void(const DataErrorDetail*)> handler;
};



