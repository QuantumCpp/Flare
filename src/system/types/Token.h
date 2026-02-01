#pragma once
#include "TypeToken.h"
#include <string>

struct Token{
  TypeToken type;
  std::string name;
  std::string value; //solo si es una OptionWithValue
};
