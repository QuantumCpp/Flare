#include "validation.h"
#include "../../system/types/OptionMetaData.h"
#include "../../system/types/CommandMetaData.h"
#include "../../system/registry/command/command_registry.h"
#include "../../system/registry/option/option_registry.h"
#include "../../system/registry/error/error_registry.h"
#include "../../utils/date_validator.h"
#include <charconv>
#include <unordered_set>
#include <vector>


/*
 Por convencion semantica las opciones largas (o cortas) con valor deben darse de la forma
 -e=.docx o --extension=.docx sera invalido sucesos como -e .docx o --extension .docx
 Esto para simplificar las logicas de validaciones y hacer comandos y desiciones mas
 declarativas y legibles.
*/

void ValidationTypeValueCorrect(const OptionMetaData* OptionData ,const Token& OptionToken , const DataErrorDetail* ErrorDetail);
bool IsInteger(const std::string& str);
bool IsFloat(const std::string& str);

bool ValidationDataToken(TokenGroup& TokenGroupRaw){
  
  std::vector<Token> GroupCommandToken = TokenGroupRaw.command;
  const std::vector<Token> GroupOptionToken = TokenGroupRaw.option;
  const CommandMetaData* CommandData;
  const OptionMetaData* OptionData;
  const DataErrorDetail* ErrorData = nullptr;

  CommandData = FindCommand(GroupCommandToken.front().name);
  //Comprobar si el comando admite las opciones introducidas
  for(size_t i = 0 ; i < GroupOptionToken.size(); i++){
    Token OptionToken = GroupOptionToken[i];
    OptionData = FindOption(OptionToken.name);
    
    if(OptionData == nullptr){
      ErrorData = GetError(ValidationError::OptionNotFound);
      ErrorData->handler(ErrorData, OptionData->default_name, std::vector<std::string>{""});
      break;
    }

    if(!CommandData->options.count(OptionToken.name)){
      ErrorData = GetError(ValidationError::OptionForWrongCommand);
      ErrorData->handler(ErrorData, CommandData->name, std::vector<std::string>{OptionToken.name});
      break; 
    }
    //Comprobar si una opcion tiene conflictos con otras introducidas
    for(size_t j = i+1 ; j < GroupOptionToken.size() ; j++){
      Token ConflictToken = GroupOptionToken[j];
      for(const auto& ElementConflict : OptionData->conflicts_with){
        if(ConflictToken.name == ElementConflict){
          ErrorData = GetError(ValidationError::ConflictingOptions);
          ErrorData->handler(ErrorData, OptionData->default_name, std::vector<std::string>{ConflictToken.name});
          break; 
        }
      }
    }

    //Comprobar si una opcion con politica de valor obligatoria tiene un valor aninado;
    if(OptionData->value_policy == ValuePolicy::Required){
      if(OptionToken.value == ""){
        ErrorData = GetError(ValidationError::OptionRequiresValue);
        ErrorData->handler(ErrorData, OptionData->default_name, std::vector<std::string>{""});
        break;  
      }
    }
    
    //Comprobar si una opcion con politica de valor no requerido tiene un valor anidado
    if(OptionData->value_policy == ValuePolicy::None){
      if(OptionToken.value != ""){
        ErrorData = GetError(ValidationError::OptionDoesNotAcceptValue);
        ErrorData->handler(ErrorData, OptionData->default_name, std::vector<std::string>{OptionToken.name});
        break;  
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
          ErrorData = GetError(ValidationError::MissingRequiredOption);
          ErrorData->handler(ErrorData, OptionData->default_name, OptionData->requieres);
          break; 
        };
      }
    }

    //Comprobar si el valor anidado a la opcion tiene el tipo de valor correcto
    if(OptionToken.value != ""){
      ValidationTypeValueCorrect(OptionData,OptionToken , ErrorData); 
      if(ErrorData){
        ErrorData->handler(ErrorData, OptionToken.name , std::vector<std::string>{OptionToken.value});
        break; 
      };
    }

  }

  if(ErrorData){
     return false;
  }

  return true;
}

/*
 Solo se hacen validaciones para enteros, flotantes y fechas debido a que todo se introduce en string, no tendria sentido
 analizar si es string, los path pueden ser de formato absoluto o relativo asi que se deja esa validacion del string a la hora
 de usar la opcion.
 El date lo analizo porque si deben de seguir un formato YYYY-MM-DD
*/

void ValidationTypeValueCorrect(const OptionMetaData* OptionData ,const Token& OptionToken,const DataErrorDetail* ErrorDetail){
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
        ErrorDetail = GetError(ValidationError::InvalidValueType_Integer);
        ErrorDetail->handler(ErrorDetail, OptionToken.name , std::vector<std::string>{""});
      };
      break;
    case ValueType::Float:
      if(!IsFloat(OptionToken.value)){
        ErrorDetail = GetError(ValidationError::InvalidValueType_Float);
        ErrorDetail->handler(ErrorDetail, OptionToken.name , std::vector<std::string>{""});
        
      }
      break;
    case ValueType::Date:
      if(!isValidatedDate(OptionToken.value)){
        ErrorDetail = GetError(ValidationError::InvalidValueType_Date);
        ErrorDetail->handler(ErrorDetail, OptionToken.name , std::vector<std::string>{OptionToken.value});
        
      }
      break;

    default:
      break;
  }

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
