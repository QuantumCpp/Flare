#pragma once
#include <string>
#include <functional>
#include <vector>
#include <unordered_map>
#include "OptionMetaData.h"
#include "TokenGroup.h"
#include "ValuePolicy.h"


struct CommandMetaData{
  std::string name;
  std::string description;
  std::vector<std::string> usage_example;
  std::unordered_map<std::string,const OptionMetaData* > options;
  ValuePolicy value_policy;

  std::function<bool(const TokenGroup& )> handler;
};
