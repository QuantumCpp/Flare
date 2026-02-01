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
#include "system/registry/error/error_registry.h"


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
  
  //Realizar el proceso de clasificacion
  ValidationError ErrorSuccess = ClasificationDataToken(TokenRaw, TokenGroupRaw);
  const DataErrorDetail* ErrorDetail;
  
  if(ErrorSuccess != ValidationError::AllCorrect){
    ErrorDetail = GetError(ErrorSuccess);
    if(ErrorDetail){
      ErrorDetail->handler(ErrorDetail);
    }
    return 1;
  };
  
  //Realiar proceso de validacion
  ErrorSuccess = ValidationDataToken(TokenGroupRaw); 
  if(ErrorSuccess != ValidationError::AllCorrect){
    ErrorDetail = GetError(ErrorSuccess);
    if(ErrorDetail){
      ErrorDetail->handler(ErrorDetail);  
    }
    return 1;
  };

  //Realizar proceso de ejecucion
  ErrorSuccess = ExecutedProccess(TokenGroupRaw);
  if(ErrorSuccess != ValidationError::AllCorrect){
    ErrorDetail = GetError(ErrorSuccess);
    if(ErrorDetail){
      ErrorDetail->handler(ErrorDetail);
    }
    return 1;
  }

  return 0;

}
