#pragma once
#include  <vector>
#include <string>
#include "ValuePolicy.h"
#include "ValueType.h"

struct OptionMetaData{
  std::vector<std::string> names;
  std::string description;
  ValuePolicy value_policy;
  ValueType value_type;
  std::string default_name;
  std::vector<std::string> conflicts_with;
  std::vector<std::string> requieres;
};


