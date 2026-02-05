#pragma once
#include "../../types/OptionMetaData.h"
#include <string>

void RegisterOption(const OptionMetaData& option);
const OptionMetaData* FindOption(const std::string& name);
