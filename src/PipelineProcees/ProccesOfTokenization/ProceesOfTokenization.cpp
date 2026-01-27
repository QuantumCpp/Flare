#include "ProccesOfTokenization.h"

std::vector<Token> Tokenization(const std::vector<std::string>& args){
  std::vector<Token> token;
  bool CommandFound = false;
  bool OnlyPositionArguments = false;

  for(size_t i = 0 ; i < args.size() ; i++){
    std::string arguments = args[i];
    
    if(arguments == "c-files"){
      continue;
    }

    if(arguments.empty()){
      continue;
    }

    //Comprobacion si solo se aceptaran argumentos posicionales
    if(arguments == "--"){
      OnlyPositionArguments = true;
      continue;
    }

    //Comprobacion del comando principal en la posicion 0
    if(i == 0 && !CommandFound && !OnlyPositionArguments && !StartWith(arguments,"-")){
      token.emplace_back(Token{TypeToken::Command , arguments , ""});
      CommandFound = true;
      continue;
    }

    if(StartWith(arguments, "-") && !OnlyPositionArguments){
      //Tratamiento para opciones con valor especificado
      if(StartWith(arguments,"--")){
        auto equal = arguments.find("=");
        
        //Si el argumento posee un simbolo de igual se extrae y se copia el nombre de la opcion, mas el valor especificado 
        if(equal != std::string::npos){
          token.emplace_back(Token{TypeToken::Option , arguments.substr(0 , equal) , arguments.substr(equal + 1)});
          continue;
        }
        
        //Si el argumento es un opcion larga sin valor adjunto con un signo de igual tambien se guarda pero con un valor string ""
        else{
          token.emplace_back(Token{TypeToken::Option, arguments, ""});
          continue;
        }
      }

      //Separacion de opciones cortas aninadas (-abc) en tokens diferentes
      if(arguments.size() > 2 && !StartWith(arguments, "--")){
        for(const auto& element : arguments){
          if(element == '-'){
            continue;
          }
          std::string NewElement  = "";
          NewElement.push_back(element);
          token.emplace_back(Token{TypeToken::Option, "-" + NewElement, ""});
        }
        continue;
      }

      //Tokenizacion de flags (-a) 
      token.emplace_back(Token{TypeToken::Option , arguments, ""});
      continue;

    }

    //Tokenizacion de argumentos posicionales
    token.emplace_back(Token{TypeToken::Positional, arguments, ""});

  }

  return token;
}
