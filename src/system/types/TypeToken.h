#pragma once
#include <cstdint>

enum class TypeToken : std::uint8_t{
  Command = 0,
  Option = 1,
  Literal = 2,
  Separation= 3,
  Positional = 4,
};
