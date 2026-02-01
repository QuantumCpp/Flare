#include "option_registry.h"
#include <unordered_map>

static std::unordered_map<std::string,OptionMetaData> optionTable;

void RegisterOption(const OptionMetaData& option){
  for (const auto& name :option.names){
    optionTable[name] = option;
  }
}

const OptionMetaData* FindOption(const std::string& name){
  auto it = optionTable.find(name);
  if (it == optionTable.end()){
    return nullptr;
  }
  return &it->second;
}
