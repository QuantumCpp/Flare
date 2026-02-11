#include "date_validator.h"
#include <regex>
#include <sstream>
#include <string>
#include <chrono>

bool isValidatedDate(const std::string &str){
  std::regex pattern(R"(^\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01])$)");
  return std::regex_match(str, pattern);
}



bool isValidateContexDate(const std::string& str){
  bool validate_date = true;
  std::istringstream string_date(str);
  std::chrono::sys_days parser_date;

  string_date >> std::chrono::parse("%F", parser_date);

  std::chrono::year_month_day year_month_day(parser_date);
  if(!year_month_day.ok()){
    validate_date = false;
  }


  return validate_date;
}
