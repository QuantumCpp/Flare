#include "tokenization.h"
#include <stdexcept>
#include <unordered_set>
#include <vector>
#include <string>
#include "../../system/types/Token.h"
#include "../../system/types/TypeToken.h"
#include "../../system/types/CommandMetaData.h"
#include "../../system/registry/command/command_registry.h"
#include "system/registry/option/option_registry.h"
#include "system/types/OptionMetaData.h"
#include "system/types/ValuePolicy.h"
#include "system/types/ValueType.h"
#include <ranges>

std::vector<Token> Parser(const std::vector<Token>& container_token_raw);

std::vector<Token> Tokenization(const std::vector<std::string>& args){
  std::vector<Token> container_token_raw;
  container_token_raw.reserve(args.size());
  bool CommandFound = false;
  bool OnlyPositionArguments = false;

  for(const auto& Arguments : args | std::views::filter([](auto& str){return !str.empty();})){
    
    //ignorar argumentos del tipo ""
    if(Arguments.empty()){
      continue;
    } 

    //Guardar el primer elemento (sin importar cual sea) como comando
    if(!CommandFound && !OnlyPositionArguments && !Arguments.starts_with("-")){
      container_token_raw.emplace_back(Token{.type = TypeToken::Command ,
                               .name = Arguments ,
                               .value = ""});
      CommandFound = true;
      continue;
    }

    //Comprobacion si solo se aceptaran argumentos posicionales
    if(Arguments == "--"){
      container_token_raw.emplace_back(Token{.type = TypeToken::Separation, 
                               .name = Arguments,
                               .value =  ""});
      OnlyPositionArguments = true;
      continue;
    }
    
    //Idendificar de forma general los options largos y cortos
    if(Arguments.starts_with("-") && !OnlyPositionArguments){
       container_token_raw.emplace_back(Token{.type = TypeToken::Option,
                             .name =  Arguments,
                             .value = ""});
      continue;
    }
       //Tokenizacion de argumentos posicionales
      container_token_raw.emplace_back(Token{.type = TypeToken::Literal,
                             .name =  Arguments,
                             .value = ""});
  }

  std::vector<Token> container_token_validated = Parser(container_token_raw);

  return container_token_validated;
}


std::vector<Token> Parser(const std::vector<Token>& container_token_raw){
  std::vector<Token> container_token_process;
  bool separation_exist = false;
  std::unordered_set<std::string> see_arguments;

  for(size_t i = 0 ; i < container_token_raw.size() ; i++){
    Token individual_token = container_token_raw[i];
    
    if(see_arguments.contains(individual_token.name)){
      continue;
    }

    if(individual_token.type == TypeToken::Command){
      container_token_process.emplace_back(individual_token);
      continue;
    }
    if(individual_token.type == TypeToken::Separation){
      separation_exist = true;
      continue;
    }
    if(separation_exist){
      container_token_process.emplace_back(Token{.type = TypeToken::Positional,
                                                 .name = individual_token.name,
                                                 .value = ""}); 
      continue;
    }

    if(individual_token.type == TypeToken::Option){
      Token token_analisys = individual_token;
      const OptionMetaData* data_option = FindOption(individual_token.name);
      //verificar si una opcion tiene dentro de si un =
      auto its = individual_token.name.find(std::string("="));
      if(its != std::string::npos){
        token_analisys.name = data_option->default_name;
        token_analisys.value = individual_token.name.substr(its + 1);
        continue;
      }
      //verificacion en caso de que el siguiente valor al actual sea un literal y la opcion actual requiera de un valor 
      if(data_option->value_policy == ValuePolicy::Required && individual_token.value.empty()){
        try{
          const auto& posible_value = container_token_raw.at(i + 1);
          if(posible_value.type == TypeToken::Literal){
            token_analisys.value = posible_value.name;
            see_arguments.insert(token_analisys.name);
          }
          container_token_process.emplace_back(token_analisys);
          continue;

        }catch (const std::out_of_range& e){
          continue;
        }
      }
    }
    if(individual_token.type == TypeToken::Literal){
      container_token_process.emplace_back(Token{.type = TypeToken::Positional,
                                                 .name = individual_token.name,
                                                 .value = "",
          });                              
    }
  }
  return container_token_process;
}

