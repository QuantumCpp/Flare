#include "tokenization.h"
#include <stdexcept>
#include <unordered_set>
#include <vector>
#include <string>
#include "../../system/types/Token.h"
#include "../../system/types/TypeToken.h"
#include "system/registry/option/option_registry.h"
#include "system/types/OptionMetaData.h"
#include "system/types/ValuePolicy.h"
#include <ranges>
#include <iostream>
#include <format>

namespace  {
  
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

      if(individual_token.type == TypeToken::LongOption || individual_token.type == TypeToken::ShortOption){
        Token token_analisys = individual_token;
        const OptionMetaData* data_option;

      //verificar si una opcion tiene dentro de si un =
        auto its = individual_token.name.find(std::string("="));
        if(its != std::string::npos){
          data_option = FindOption(individual_token.name.substr(0,its-1));
          if(data_option != nullptr){
            token_analisys.type = TypeToken::OptionGeneral;
            token_analisys.name = data_option->default_name;
            token_analisys.value = individual_token.name.substr(its + 1);
          }
          else{
            token_analisys.type = TypeToken::OptionGeneral;
            token_analisys.name = individual_token.name.substr(0,its);
            token_analisys.value = individual_token.name.substr(its + 1);
          }
          container_token_process.emplace_back(token_analisys);
          continue;
        }
      
      //Si no hay opcion valida devuelve error, evitara segmentation fault 
        data_option = FindOption(individual_token.name);
        if(data_option == nullptr){
          token_analisys.type = TypeToken::OptionGeneral;
          container_token_process.emplace_back(token_analisys);
          continue;
        }

      //verificacion en caso de que el siguiente valor al actual sea un literal y la opcion actual requiera de un valor 
        if(data_option->value_policy == ValuePolicy::Required && individual_token.value.empty()){
          try{
            const auto& posible_value = container_token_raw.at(i + 1);
            if(posible_value.type == TypeToken::Literal){
              token_analisys.type = TypeToken::OptionGeneral;
              token_analisys.value = posible_value.name;
              see_arguments.insert(posible_value.name);
            }
            container_token_process.emplace_back(token_analisys);
            continue;
          }catch (const std::out_of_range& e){
            token_analisys.type = TypeToken::OptionGeneral;
            container_token_process.emplace_back(token_analisys);
            continue;
          }
        }
      
      //Separar argumentos en caso de que se presenten de la forma -abc en -a | -b | -c
        if(individual_token.name.starts_with("-")&&
            individual_token.name.size() > 2 ){

          for(const auto& element : individual_token.name){
            if(element == '-'){
              continue;
            }
            container_token_process.emplace_back(Token{.type = TypeToken::OptionGeneral, 
                                                     .name = std::string("-") + element,
                                                     .value = ""});
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

  void TEST_TOKENIZATION(const std::vector<Token>& container){
    std::cout << std::format("\n{:<10}{:>20}{:>20}\n", "ARGUMENTO" , "TIPO" , "VALOR");
    for(const auto& elemento : container){

    std::string tipo;
    switch (elemento.type) {
      case TypeToken::Command:
        tipo = "COMANDO";
        break;
      case TypeToken::LongOption:
        tipo = "OPCION LARGA";
        break;
      case TypeToken::ShortOption:
        tipo = "OPCION CORTA";
        break;
      case TypeToken::Literal:
        tipo = "LITERAL";
        break;
      case TypeToken::Positional:
        tipo = "POSICIONAL";
        break;
      case TypeToken::Separation:
        tipo = "SEPARACION";
        break;
      case TypeToken::OptionGeneral:
        tipo = "OPCION GENERAL";
        break;
    }
    std::cout<< std::format("{:<10}{:>20}{:>20}\n", elemento.name , tipo, elemento.value);
  }
  }

}

std::vector<Token> Tokenization(const std::vector<std::string>& args){
  std::vector<Token> container_token_raw;
  container_token_raw.reserve(args.size());
  bool CommandFound = false;
  bool OnlyPositionArguments = false;

  for(const auto& Arguments : args | std::views::filter([](auto& str){return !str.empty();})){

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
      if(Arguments.starts_with("--")){
        container_token_raw.emplace_back(Token{.type = TypeToken::LongOption,
                             .name =  Arguments,
                             .value = ""});
        continue;
      }
       container_token_raw.emplace_back(Token{.type = TypeToken::ShortOption,
                             .name =  Arguments,
                             .value = ""});
        continue;
    }

       //Tokenizacion de argumentos posicionales
      container_token_raw.emplace_back(Token{.type = TypeToken::Literal,
                             .name =  Arguments,
                             .value = ""});
  }
  
  TEST_TOKENIZATION(container_token_raw);

  std::vector<Token> container_token_validated = Parser(container_token_raw);

  TEST_TOKENIZATION(container_token_validated);

  return container_token_validated;
}

