#include "tokenization.h"
#include "../../utils/string_utils.h"

std::vector<Token> Tokenization(const std::vector<std::string>& args){
  std::vector<Token> token;
  bool CommandFound = false;
  bool OnlyPositionArguments = false;

  for(size_t i = 0 ; i < args.size() ; i++){
    std::string Arguments = args[i];
    
    //ignorar argumentos del tipo ""
    if(Arguments.empty()){
      continue;
    } 

    //Guardar el primer elemento (sin importar cual sea) como comando
    if(!CommandFound && !OnlyPositionArguments && !StartWith(Arguments,"-")){
      token.emplace_back(Token{TypeToken::Command , Arguments , ""});
      CommandFound = true;
      continue;
    }

    //Comprobacion si solo se aceptaran argumentos posicionales
    if(Arguments == "--"){
      token.emplace_back(Token{TypeToken::Separation, Arguments, ""});
      OnlyPositionArguments = true;
      continue;
    }
    
    //Idendificar de forma general los options largos y cortos
    if(StartWith(Arguments, "-") && !OnlyPositionArguments){
      //Tratamiento para opciones con valor especificado
      if(StartWith(Arguments,"--")){
        auto EqualPos = Arguments.find("=");
        
        //Si el argumento posee un simbolo de igual se extrae y se copia el nombre de la opcion, mas el valor especificado 
        if(EqualPos != std::string::npos){
          token.emplace_back(Token{TypeToken::Option , Arguments.substr(0 , EqualPos) , Arguments.substr(EqualPos + 1)});
          continue;
        }
        
        //Si el argumento es un opcion larga sin valor adjunto con un signo de igual tambien se guarda pero con un valor string ""
        else{
          token.emplace_back(Token{TypeToken::Option, Arguments, ""});
          continue;
        }
      }

      //Separacion de opciones cortas aninadas (-abc) en tokens diferentes
      if(Arguments.size() > 2 && !StartWith(Arguments, "--")){
        for(const auto& element : Arguments){
          if(element == '-'){
            continue;
          }
          std::string NewElement  = "";
          NewElement.push_back(element);
          token.emplace_back(Token{TypeToken::Option, "-" + NewElement, ""});
        }
        continue;
      }

      //Tokenizacion de flags (-a) u opcion larga sin valor (--help) 
      token.emplace_back(Token{TypeToken::Option , Arguments, ""});
      continue;

    }

    //Tokenizacion de argumentos posicionales
    token.emplace_back(Token{TypeToken::Positional, Arguments, ""});

  }

  return token;
}
