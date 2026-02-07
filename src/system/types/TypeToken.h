#pragma once
#include <cstdint>

enum class TypeToken : std::uint8_t{
  Command = 0,
  OptionGeneral = 1,
  Literal = 2,
  Separation= 3,
  Positional = 4,
  LongOption = 5,
  ShortOption = 6
};
