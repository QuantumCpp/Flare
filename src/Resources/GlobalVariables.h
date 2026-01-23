#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <filesystem> 

//Comandos:
//1.Listar archivos : Fecha de creacion - Nombre - Extension - Tamano 

enum class TypeToken{
  Command,
  Option,
  Separation,
  OptionGroup,
  Positional
};

enum class ValuePolicy{
  None,
  Required,
  Optional
};

enum class ValidationError{
  AllCorrect,
  CommandIncorrectPosition,
  CommandNotFound,
  OptionNotFound,
  OptionRequiredValue,
  OptionNotRequiredValue
} ;

struct Token{
  TypeToken type;
  std::string name;
  std::string value; //solo si es una OptionWithValue
};

const std::unordered_map<std::string,ValuePolicy> CommandSpec = {
    {"list" , ValuePolicy::None}
  };
const std::unordered_map<std::string,ValuePolicy> OptionSpec = {
    {"--extension", ValuePolicy::Required},
    {"-e" , ValuePolicy::None},
    {"-s" , ValuePolicy::None},
    {"-d" , ValuePolicy::None},

  };

bool StartWith(const std::string& arg, const std::string& start){
  return !arg.empty() && arg.find(start) == 0;
}
