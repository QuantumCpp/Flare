#include "GlobalVariables.h"

ValidationError Validation(std::vector<Token>& tokens){
  
  for (size_t i = 0 ; i < tokens.size() ; i ++){
    Token token = tokens[i];
    
    if (i == 0){
      if(tokens[i].type != TypeToken::Command){
        return ValidationError::CommandIncorrectPosition;
      }
    }

    //Validar que un comando existe : 
    if (token.type == TypeToken::Command){
      if (CommandSpec.find(token.name) != CommandSpec.end()){
        continue;
      }
      else{
        return ValidationError::CommandNotFound;
      }
    }
    
    if(token.type == TypeToken::Option){
      if (OptionSpec.find(token.name)  != OptionSpec.end()){
        if((OptionSpec.at(token.name) == ValuePolicy::None && token.value == "") ||  
            (OptionSpec.at(token.name) == ValuePolicy::Required && token.value != ""))
        {
          continue;
        }

         if (OptionSpec.at(token.name) == ValuePolicy::None && token.value != "") {return ValidationError::OptionNotRequiredValue; } 
         if (OptionSpec.at(token.name) == ValuePolicy::Required && token.value == "") {return ValidationError::OptionRequiredValue; }
      }
      else{
        return ValidationError::OptionNotFound;
      }
    }

  }


  return ValidationError::AllCorrect;
}

