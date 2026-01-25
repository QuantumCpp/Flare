#pragma once

#include "GlobalVariables.h"
#include <unordered_map>

ValidationError Validation(std::vector<Token>& tokens){
  
  int CommandFound = 0;
  int CantSeparationFound = 0;
  bool SeparationFound = false;

  std::unordered_map<std::string ,int>SeenOption;

  for (size_t i = 0 ; i < tokens.size() ; i ++){
    Token token = tokens[i];
    
    //Comando en posicion incorrecta
    if (i == 0){
      if(tokens[i].type != TypeToken::Command){
        return ValidationError::CommandIncorrectPosition;
      }
    }

    //Validar que un comando existe y solo hay uno : 
    if (token.type == TypeToken::Command){
      if (CommandSpec.find(token.name) != CommandSpec.end()){
        CommandFound += 1;
        if (CommandFound > 1){
          return ValidationError::MoreOfCommand;
        }
        continue;
      }
      else{
        return ValidationError::CommandNotFound;
      }
    }
    
    if(token.type == TypeToken::Option){

      if (SeenOption[token.name]){
        tokens.erase(tokens.begin() + i);
        --i;
        continue;
      }

      if (OptionSpec.find(token.name)  != OptionSpec.end()){

        if((OptionSpec.at(token.name) == ValuePolicy::None && token.value == "") ||  
            (OptionSpec.at(token.name) == ValuePolicy::Required && token.value != ""))
        {
          SeenOption[token.name] = true;
          continue;
        }
         if (OptionSpec.at(token.name) == ValuePolicy::None && token.value != "") 
         {
           return ValidationError::OptionNotRequiredValue; 
         } 
         if (OptionSpec.at(token.name) == ValuePolicy::Required && token.value == "") 
         {
           return ValidationError::OptionRequiredValue; 
         }
      }
      else{
        return ValidationError::OptionNotFound;
      }
    }

    if(token.type == TypeToken::Separation){
      SeparationFound = true;
      CantSeparationFound++;
      continue;
    }

    if (SeparationFound == true && CantSeparationFound == 1){
      tokens[i].type = TypeToken::Positional;
    }

    if (CantSeparationFound > 1){
      return ValidationError::MoreSeparationSignal;
    }

  }

  return ValidationError::AllCorrect;
}

