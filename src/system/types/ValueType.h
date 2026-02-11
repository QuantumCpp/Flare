#pragma once
#include <cstdint>

enum class ValueType : std::uint8_t{
  None = 0, //no requiere nada
  String = 1, //Requiere un string
  Integer = 2, //Requiere un entero
  Float = 3, //Requiere un valor flotante
  Path = 4, //Requiere un directorio
  Date = 5, //Formato YYYY-MM-DD
  Size = 6, //Date - Size - Name
};
