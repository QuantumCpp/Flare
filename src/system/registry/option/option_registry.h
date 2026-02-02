#pragma once
#include "../../types/OptionMetaData.h"

void RegisterOption(const OptionMetaData& option);
const OptionMetaData* FindOption(const std::string& name);
