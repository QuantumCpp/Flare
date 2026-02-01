#include "validation.h"
#include "../../system/types/OptionMetaData.h"
#include "../../system/types/CommandMetaData.h"
#include "../../system/registry/command/command_registry.h"
#include "../../system/registry/option/option_registry.h"
#include <unordered_set>
#include "../../utils/date_validator.h"
#include <charconv>

/*
 Por convencion semantica las opciones largas (o cortas) con valor deben darse de la forma
 -e=.docx o --extension=.docx sera invalido sucesos como -e .docx o --extension .docx
 Esto para simplificar las logicas de validaciones y hacer comandos y desiciones mas
 declarativas y legibles.
*/

ValidationError ValidationTypeValueCorrect(const OptionMetaData* OptionData ,const Token& OptionToken);
bool IsInteger(const std::string& str);
bool IsFloat(const std::string& str);

ValidationError ValidationDataToken(TokenGroup& TokenGroupRaw){
  
  std::vector<Token> GroupCommandToken = TokenGroupRaw.command;
  const std::vector<Token> GroupOptionToken = TokenGroupRaw.option;
  const CommandMetaData* CommandData;
  const OptionMetaData* OptionData;

  CommandData = FindCommand(GroupCommandToken.front().name);
  //Comprobar si el comando admite las opciones introducidas
  for(size_t i = 0 ; i < GroupOptionToken.size(); i++){
    Token OptionToken = GroupOptionToken[i];
    OptionData = FindOption(OptionToken.name);
    
    if(OptionData == nullptr){
      return ValidationError::OptionNotFound;
    }

    if(!CommandData->options.count(OptionToken.name)){
      return ValidationError::OptionForWrongCommand;
    }
    //Comprobar si una opcion tiene conflictos con otras introducidas
    for(size_t j = i+1 ; j < GroupOptionToken.size() ; j++){
      Token ConflictToken = GroupOptionToken[j];
      for(const auto& ElementConflict : OptionData->conflicts_with){
        if(ConflictToken.name == ElementConflict){
          return ValidationError::ConflictingOptions;
        }
      }
    }

    //Comprobar si una opcion con politica de valor obligatoria tiene un valor aninado;
    if(OptionData->value_policy == ValuePolicy::Required){
      if(OptionToken.value == ""){
        return ValidationError::OptionRequiresValue;
      }
    }
    
    //Comprobar si una opcion con politica de valor no requerido tiene un valor anidado
    if(OptionData->value_policy == ValuePolicy::None){
      if(OptionToken.value != ""){
        return ValidationError::OptionDoesNotAcceptValue;
      }
    }

    //Comprobar (para las opciones que requieren otras opciones) si tienen opciones requeridas
    if(!OptionData->requieres.empty()){
      
      std::unordered_set<std::string> SetToken;
      for(const auto& RequiresToken : OptionData->requieres){
        SetToken.insert(RequiresToken);
      }

      for(const auto& ElementExist : OptionData->requieres){
        if(SetToken.count(ElementExist) == 0){
          return ValidationError::MissingRequiredOption;
        };
      }
    }

    //Comprobar si el valor anidado a la opcion tiene el tipo de valor correcto
    if(OptionToken.value != ""){
      ValidationError Error = ValidationTypeValueCorrect(OptionData,OptionToken); 
      if(Error != ValidationError::AllCorrect){
        return Error;
      };
    }

  }

  return ValidationError::AllCorrect;
}

/*
 Solo se hacen validaciones para enteros, flotantes y fechas debido a que todo se introduce en string, no tendria sentido
 analizar si es string, los path pueden ser de formato absoluto o relativo asi que se deja esa validacion del string a la hora
 de usar la opcion.
 El date lo analizo porque si deben de seguir un formato YYYY-MM-DD
*/

ValidationError ValidationTypeValueCorrect(const OptionMetaData* OptionData ,const Token& OptionToken){
  switch(OptionData->value_type){
    case ValueType::None:
      break;

    case ValueType::Enum:
      break;

    case ValueType::Path:
      break;

    case ValueType::String:
      break;

    case ValueType::Integer:
      if(!IsInteger(OptionToken.value)){
        return ValidationError::InvalidValueType_Integer;
      };
      break;
    case ValueType::Float:
      if(!IsFloat(OptionToken.value)){
        return ValidationError::InvalidValueType_Float;
      }
      break;
    case ValueType::Date:
      if(!isValidatedDate(OptionToken.value)){
        return ValidationError::InvalidValueType_Date;
      }
      break;

    default:
      break;
  }


  return ValidationError::AllCorrect;
}

bool IsInteger(const std::string& str){
  int value ;
  auto conversion = std::from_chars(str.data(), str.data() + str.size(),value );
  return conversion.ec == std::errc() && conversion.ptr == str.data() + str.size();  
}

bool IsFloat(const std::string& str){
  float value;
  auto conversion = std::from_chars(str.data(), str.data() + str.size(), value);
  return conversion.ec == std::errc() && conversion.ptr == str.data() + str.size();
}
