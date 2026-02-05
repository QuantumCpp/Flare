#ifndef OPTION_META_DATA
#define OPTION_META_DATA 

#include <vector>
#include <string>
#include "ValuePolicy.h"
#include "ValueType.h"
#include "OptionContex.h"
#include "OptionProcessType.h"

struct OptionMetaData{
  std::vector<std::string> names;
  std::string description;
  ValuePolicy value_policy;
  ValueType value_type;
  std::string default_name;
  std::vector<std::string> conflicts_with;
  std::vector<std::string> requieres;
  
  OptionProcessType process_type;

  OptionHandler handler;
};

#endif // OPTION_META_DATA



