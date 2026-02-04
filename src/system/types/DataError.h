#pragma once
#include <functional>
#include <string> 
#include "ValidationError.h"
#include <vector>

struct DataErrorDetail{
  ValidationError ErrorID;
  std::string NameError;
  std::string ShortDetail;

  std::function<void(const DataErrorDetail*,const std::string&, const std::vector<std::string>& )> handler;
};



