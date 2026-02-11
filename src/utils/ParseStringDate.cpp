#include <chrono>
#include <sstream>
#include <string>
#include <stdexcept>

std::chrono::sys_days ParseStringDate(const std::string& string_date){
  std::istringstream string_parser(string_date);
  std::chrono::sys_days parser_date;
  string_parser >> std::chrono::parse("%Y-%d-%m", parser_date);

  if(string_parser.fail()){
    throw std::runtime_error("Formato invalido");
  }

  std::chrono::year_month_day ymd{parser_date};
  if(!ymd.ok()){
    throw std::runtime_error("Fecha invalida");
  }

  return parser_date;
}
