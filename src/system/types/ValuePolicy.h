#pragma once

#include <cstdint>

enum class ValuePolicy : std::uint8_t{
  None,
  Required,
  Optional
};
