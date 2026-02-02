#include "string_utils.h"

bool StartWith(const std::string& arg, const std::string& start){
  return !arg.empty() && arg.find(start) == 0;
}
