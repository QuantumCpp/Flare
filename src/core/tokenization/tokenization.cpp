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
#include <cstddef>

namespace {
  
  std::vector<Token> Parser(const std::vector<Token>& container_token_raw){
    std::vector<Token> container_token_process;
    container_token_process.reserve(container_token_raw.size());
    bool separation_exist = false;
    std::unordered_set<std::string> see_arguments;

    for(size_t i = 0; i < container_token_raw.size(); i++){
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
        const OptionMetaData* data_option = nullptr;

        // Verificar si una opción tiene dentro de sí un =
        auto its = individual_token.name.find("=");
        if(its != std::string::npos){
          // Buscar la opción sin el valor (antes del =)
          data_option = FindOption(individual_token.name.substr(0, its));
          if(data_option != nullptr){
            // Opción encontrada en el registro
            token_analisys.type = TypeToken::OptionGeneral;
            token_analisys.name = data_option->default_name;
            token_analisys.value = individual_token.name.substr(its + 1);
          }
          else{
            // Opción NO encontrada en el registro - extraer manualmente
            token_analisys.type = TypeToken::OptionGeneral;
            token_analisys.name = individual_token.name.substr(0, its);
            token_analisys.value = individual_token.name.substr(its + 1);
          }
          container_token_process.emplace_back(token_analisys);
          continue;
        }
      
        // Buscar la opción en el registro
        data_option = FindOption(individual_token.name);
        
        // Si no hay opción válida, agregarla como está
        if(data_option == nullptr){
          token_analisys.type = TypeToken::OptionGeneral;
          container_token_process.emplace_back(token_analisys);
          continue;
        }

        // Verificar si la opción requiere un valor y el siguiente token es un literal
        if(data_option->value_policy == ValuePolicy::Required && individual_token.value.empty()){
          try{
            const auto& posible_value = container_token_raw.at(i + 1);
            if(posible_value.type == TypeToken::Literal){
              token_analisys.type = TypeToken::OptionGeneral;
              token_analisys.name = data_option->default_name;
              token_analisys.value = posible_value.name;
              see_arguments.insert(posible_value.name);
              container_token_process.emplace_back(token_analisys);
              continue;
            }
          }catch (const std::out_of_range& e){
            // No hay siguiente token, agregar sin valor
            token_analisys.type = TypeToken::OptionGeneral;
            token_analisys.name = data_option->default_name;
            container_token_process.emplace_back(token_analisys);
            continue;
          }
        }
      
        // Separar argumentos cortos agrupados: -abc → -a, -b, -c
        if(individual_token.name.starts_with("-") && 
           !individual_token.name.starts_with("--") &&
           individual_token.name.size() > 2){
          for(const auto& element : individual_token.name){
            if(element == '-'){
              continue;
            }
            container_token_process.emplace_back(Token{.type = TypeToken::OptionGeneral, 
                                                     .name = std::string("-") + element,
                                                     .value = ""});
          }
          continue;
        }

        // Opción válida sin requisitos especiales
        token_analisys.type = TypeToken::OptionGeneral;
        token_analisys.name = data_option->default_name;
        container_token_process.emplace_back(token_analisys);
        continue;
      }

      if(individual_token.type == TypeToken::Literal){
        container_token_process.emplace_back(Token{.type = TypeToken::Positional,
                                                 .name = individual_token.name,
                                                 .value = ""});
        continue;                              
      }
    }
    return container_token_process;
  }

}

std::vector<Token> Tokenization(const std::vector<std::string>& args){
  std::vector<Token> container_token_raw;
  container_token_raw.reserve(args.size());
  bool CommandFound = false;
  bool OnlyPositionArguments = false;

  for(const auto& Arguments : args | std::views::filter([](auto& str){return !str.empty();})){

    // Guardar el primer elemento (sin importar cuál sea) como comando
    if(!CommandFound && !OnlyPositionArguments && !Arguments.starts_with("-")){
      container_token_raw.emplace_back(Token{.type = TypeToken::Command,
                               .name = Arguments,
                               .value = ""});
      CommandFound = true;
      continue;
    }

    // Comprobación si solo se aceptarán argumentos posicionales
    if(Arguments == "--"){
      container_token_raw.emplace_back(Token{.type = TypeToken::Separation, 
                               .name = Arguments,
                               .value = ""});
      OnlyPositionArguments = true;
      continue;
    }
    
    // Identificar de forma general las opciones largas y cortas
    if(Arguments.starts_with("-") && !OnlyPositionArguments){
      if(Arguments.starts_with("--")){
        container_token_raw.emplace_back(Token{.type = TypeToken::LongOption,
                             .name = Arguments,
                             .value = ""});
        continue;
      }
      container_token_raw.emplace_back(Token{.type = TypeToken::ShortOption,
                             .name = Arguments,
                             .value = ""});
      continue;
    }

    // Tokenización de argumentos posicionales
    container_token_raw.emplace_back(Token{.type = TypeToken::Literal,
                             .name = Arguments,
                             .value = ""});
  }
  
  std::vector<Token> container_token_validated = Parser(container_token_raw);

  return container_token_validated;
}
