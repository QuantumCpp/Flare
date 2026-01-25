#pragma once
#include "GlobalVariables.h"
#include "utils.h"

std::vector<Token> Tokenization(std::vector<std::string> args){
  std::vector<Token> tokens;

  bool OptionOnlyPositional = false;
  bool CommandFound = false;

  for(size_t i = 0 ; i < args.size() ; i++){
    const std::string& arg = args[i];

    //Detectar solo opciones luego del --
    if(arg == "--"){
      tokens.emplace_back(Token{TypeToken::Separation, arg, ""});
      OptionOnlyPositional = true;
      continue;
    }
    
    //Detectar los comandos 
    if (!OptionOnlyPositional && !StartWith(arg,"-") && !CommandFound){
      tokens.emplace_back(Token{TypeToken::Command, arg, ""});
      CommandFound = true;
      continue;
    }
    
    //Detectar las opciones con o sin valor
    if(!OptionOnlyPositional && StartWith(arg, "-")){
      auto pos = arg.find("=");
      if(StartWith(arg,"--")){
        //Si existe el simbolo guarda la opcion y su valor asociado
        if (pos != std::string::npos){
          tokens.emplace_back(Token{TypeToken::Option, arg.substr(0, pos), arg.substr(pos + 1)});

        }

        //Si no existe tambien guarda la opcion pero sin un valor asociado
        else{
          tokens.emplace_back(Token{TypeToken::Option, arg, ""});
        }
        continue;
      }

      if(arg.size() > 2 && !StartWith(arg,"--")){
        for(const auto& element : arg){
          std::string str = "";
          if(element == '-'){
            continue;
          }
          str.push_back(element);
          tokens.emplace_back(Token{TypeToken::Option, "-" + str, ""});
          continue;
        }
      }

      if(arg.size() == 2 && !StartWith(arg,"--")){
        tokens.emplace_back(Token{TypeToken::Option, arg, ""});
        continue;
      }
    }

    if ((OptionOnlyPositional || !StartWith(arg,"-")) && CommandFound){
      tokens.emplace_back(Token{TypeToken::Positional, arg, ""});
      continue;
    }
  }
  return tokens;

}

