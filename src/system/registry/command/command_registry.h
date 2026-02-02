#pragma once
#include <string>
#include "../../types/CommandMetaData.h"

void CommandRegister(const CommandMetaData& command);
const CommandMetaData* FindCommand(const std::string& name);
