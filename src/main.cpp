#include "SystemUtilites/EnumsClass/ValidationError.h"
#include "SystemUtilites/MessageErrorDetail/RegisterError/RegisterError.h"
#include "SystemUtilites/Structs/DataError.h"
#include "SystemUtilites/Structs/TokenGroup.h"
#include "Utils/RegisterAllCommands/RegisterAllCommands.h"
#include "Utils/RegisterAllOptions/RegisterAllOptions.h"
#include "PipelineProcees/ProccesOfTokenization/ProccesOfTokenization.h"
#include "PipelineProcees/ProccesOfClasification/ProceesOfClasification.h"
#include "PipelineProcees/ProceesOfValidationTokens/ProceesOfValidationTokens.h"
#include "PipelineProcees/ProccessOfExcute/Execute.h"
#include "SystemUtilites/MessageErrorDetail/MessageError.h"


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
  ErrorSuccess = ValidationDataToken(TokenRaw,TokenGroupRaw); 
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
