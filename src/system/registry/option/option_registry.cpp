#include "option_registry.h"
#include <unordered_map>
#include <string>
#include "../../types/OptionMetaData.h"

static std::unordered_map<std::string,OptionMetaData> optionTable;

void RegisterOption(const OptionMetaData& option){
  for (const auto& name :option.names){
    optionTable[name] = option;
  }
}

const OptionMetaData* FindOption(const std::string& name){
  auto its = optionTable.find(name);
  if (its == optionTable.end()){
    return nullptr;
  }
  return &its->second;
}
