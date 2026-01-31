#include "Execute.h"

ValidationError ExecuteProccess(const TokenGroup& TokenGroupValidate){
  //Seleccionamos el tope del token group debido a que solo deberia haber uno no habra problema
  Token CommandSelect = TokenGroupValidate.command.front();
  
  if(CommandSelect.name == "list"){
  }

  return ValidationError::AllCorrect;
}
