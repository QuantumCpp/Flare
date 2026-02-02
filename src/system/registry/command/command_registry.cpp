#include "command_registry.h"

static std::unordered_map<std::string,CommandMetaData> commandTable;

void CommandRegister(const CommandMetaData& command){
  commandTable[command.name] = command;
}

const CommandMetaData* FindCommand(const std::string& name){
  auto it = commandTable.find(name);
  if(it == commandTable.end()){
    return nullptr;
  }
  return &it->second;
}


