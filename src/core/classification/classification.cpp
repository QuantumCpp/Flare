#include "classification.h"
#include "../../system/types/CommandMetaData.h"
#include "../../system/registry/command/command_registry.h"
#include "../../system/registry/option/option_registry.h"
#include "../../system/registry/error/error_registry.h"
#include <unordered_set>

/*
Clasification = Agrupacion + Normalizacion
Responsabilidades:
 1. Agrupar tokens por tipo
 2. Normalizar alias (-r -> --recurisve)
 3. Detectar duplicados
 4. Verificar que comandos/opciones existen
*/

bool ClasificationDataToken(const std::vector<Token>& tokens, TokenGroup& TokenGroupRaw){
    
  std::unordered_set<std::string> SeenOption;
  const DataErrorDetail* ErrorSucess = nullptr;

  if(tokens.empty() && !ErrorSucess){
    ErrorSucess = GetError(ValidationError::EmptyInput);
    ErrorSucess->handler(ErrorSucess,"", std::vector<std::string>{""});
    return false;
  }
  
  Token tokenFront = tokens.front();

  if(tokenFront.type != TypeToken::Command && !ErrorSucess){
    ErrorSucess = GetError(ValidationError::CommandIncorrectPosition);
    ErrorSucess->handler(ErrorSucess, "", std::vector<std::string>{""} );
    return false;
  }

  for(size_t i = 0 ; i < tokens.size() ; i++){
    Token token = tokens[i]; //Se hace una copia para poder manipularla sin afectar al original

    //Agrupar tokens por tipo 
    if(token.type == TypeToken::Command){
      const CommandMetaData* CommandData = FindCommand(token.name);
      if(!CommandData){
        ErrorSucess = GetError(ValidationError::CommandNotFound);
        ErrorSucess->handler(ErrorSucess, token.name, std::vector<std::string> {""});
        break;
      }
      else{
        TokenGroupRaw.command.emplace_back(token);
        continue;
      }
    }
    
    //Idendificar token de tipo opciones
    /*
      1. Se encarga de crear un puntero de tipo OptionMetaData y buscar si la opcion existen
      2. En caso de no exister manda un error de tipo OptionNotFound
      3. En caso de existir normalizara su nombre al default_name
      4. Se comprobara si esta opcion ya a sido vista, llevando un conteo
      - Si ya aparecio sera ignorada completamente y solo sera guardada la primera vez que aparecio
     */

    if(token.type == TypeToken::OptionGeneral){
      const OptionMetaData* OptionData = FindOption(token.name);
      if(!OptionData){
        ErrorSucess = GetError(ValidationError::OptionNotFound);
        ErrorSucess->handler(ErrorSucess,token.name,std::vector<std::string>{""});
        break;
      }
      else{
        token.name = OptionData->default_name;
        if(SeenOption.count(token.name)){
          continue;
        }
        SeenOption.insert(token.name);            

        TokenGroupRaw.option.emplace_back(token);
        continue;
      }
    }

    if(token.type == TypeToken::Positional){
      TokenGroupRaw.positional.emplace_back(token);
      continue;
    }

  }  
  if(TokenGroupRaw.command.empty() && !ErrorSucess){
    ErrorSucess = GetError(ValidationError::NoCommand);
    ErrorSucess->handler(ErrorSucess, "" , std::vector<std::string>{""});
  }

  if(TokenGroupRaw.command.size() > 1 && !ErrorSucess){
    ErrorSucess = GetError(ValidationError::MultipleCommands);
    ErrorSucess->handler(ErrorSucess, "" , std::vector<std::string>{""});
    return false;
  }
  
  if(ErrorSucess){
    return false;
  }

  return true;
}

