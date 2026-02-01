#include "date_validator.h"
#include <regex>

bool isValidatedDate(const std::string &str){
  std::regex pattern(R"(^\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01])$)");
  return std::regex_match(str, pattern);
}
