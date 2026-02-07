#include <vector>
#include <iostream>
#include "system/registry/option/register_all.h"
#include "system/registry/command/register_all.h"
#include "system/errors/data_error_register.h"
#include "system/types/Token.h"
#include "system/types/TokenGroup.h"
#include "core/tokenization/tokenization.h"
#include "core/classification/classification.h"
#include "core/validation/validation.h"
#include "core/execution/execution.h"
#include <string>
#include <format>

int main(int argc, char* argv[]){
  //Registro de todos los comandos | opciones | errores actuales
  RegisterAllCommand();
  RegisterAllOptions();
  RegisterAllError();

  //Tomar todas los argumentos en crudo dados por el usuario a excepcio del nombre del ejecutable
  std::vector<std::string> ArgumentsRaw(argv + 1, argv + argc);

  //Verificar si el ArgumentsRaw esta vacio, en caso de estarlo llamar al helper
  if(ArgumentsRaw.empty()){
    //FunctionHelper(); *Implementacion futura
    std::cerr<<"No se anadio ningun argumento";
    return 1;
  }

  //Realizar el proceso de tokenizacion y guardarlos en una variable
  std::vector<Token> TokenRaw = Tokenization(ArgumentsRaw);
  TokenGroup TokenGroupRaw;
  
  for(const auto& elemento : TokenRaw){
    std::cout << std::format("{:<10}", elemento.name);
  }
  
  //Realizar el proceso de clasificacion
  bool ErrorSuccess = ClasificationDataToken(TokenRaw, TokenGroupRaw);
  
  if(!ErrorSuccess){
    return 1;
  };
  
  //Realiar proceso de validacion
  ErrorSuccess = ValidationDataToken(TokenGroupRaw); 
  if(!ErrorSuccess){
    return 1;
  };

  //Realizar proceso de ejecucion
  ErrorSuccess = ExecutedProccess(TokenGroupRaw);
  if(!ErrorSuccess){
    return 1;
  }

  return 0;

}
