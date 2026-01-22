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
  Positional
};

enum class ValuePolicy{
  None,
  Required,
  Optional
};

struct Token{
  TypeToken type;
  std::string name;
  std::string value; //solo si es una OptionWithValue
};

bool StartWith(const std::string& arg, std::string start){
  return !arg.empty() && arg.find(start) == 0;
}

void list(std::vector<std::string> arg){

}

int main(int argc, const char* argv[] ){
  std::vector<std::string> arguments(argv + 1 , argv + argc);
  std::vector<Token> tokens;

  bool OptionOnlyPositional = false;
  bool CommandFound = false;

  std::unordered_map<std::string,ValuePolicy> CommandSpec = {
    {"list" , ValuePolicy::Optional}
  };
  std::unordered_map<std::string,ValuePolicy> OptionSpec = {
    {"--extension", ValuePolicy::Required},
    {"-e" , ValuePolicy::Optional},
    {"-s" , ValuePolicy::Optional},
    {"-d" , ValuePolicy::Optional},

  };

  for(size_t i = 0 ; i < arguments.size() ; i++){
    const std::string& args = arguments[i];

    //Detectar solo opciones luego del --
    if(args == "--"){
      OptionOnlyPositional = true;
      continue;
    }
    
    //Detectar los comandos 
    if (!OptionOnlyPositional && !StartWith(args, "-") && !CommandFound){
      tokens.emplace_back(Token{TypeToken::Command, args, ""});
      CommandFound = true;
      continue;
    }
    
    //Detectar las opciones con o sin valor
    if(!OptionOnlyPositional && StartWith(args, "-")){
      auto pos = args.find("=");
      if(StartWith(args,"--")){
        //Si existe el simbolo guarda la opcion y su valor asociado
        if (pos != std::string::npos){
          tokens.emplace_back(Token{TypeToken::Option, args.substr(0, pos), args.substr(pos + 1)});

        }
        //Si no existe tambien guarda la opcion pero sin un valor asociado
        else{
          tokens.emplace_back(Token{TypeToken::Option, args, ""});
        }
        continue;
      }

      tokens.emplace_back(Token{TypeToken::Option, args, ""});
      continue;
    }

    if ((OptionOnlyPositional || !StartWith(args,"-")) && CommandFound){
      tokens.emplace_back(Token{TypeToken::Positional, args, ""});
      continue;
    }
  }
  if(CommandFound == false){
    std::cout<<"Commmand not found\n";
  }
  else{
    std::cout<<"Command found\n";
  }
  return 0;
}

