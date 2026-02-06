#ifndef OPTION_CONTEX_H
#define OPTION_CONTEX_H

#include <filesystem>
#include <functional>
#include <variant>
#include <vector>
#include <string>
#include "OptionProcessType.h" 
#include <any>

struct FilterContext{
  std::filesystem::directory_entry& entry;
  std::any filter; 
};

struct ModifierContext{
  std::vector<std::filesystem::directory_entry>& entry;
  std::any modifier_parameter;
};

struct PrinterContext{
  std::vector<std::string>& name_directory;
  std::vector<std::filesystem::directory_entry>& name_file; 
  std::any format_printer;
};

using FilterHandler = std::function<bool(const FilterContext& )>;
using ModifierHandler = std::function<void(const ModifierContext& )>;
using PrinterHandler = std::function<void(const PrinterContext& )>;

using OptionHandler = std::variant<
  std::monostate,
  FilterHandler,
  ModifierHandler,
  PrinterHandler
>;

#endif 
