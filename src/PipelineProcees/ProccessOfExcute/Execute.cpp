#include "Execute.h"

ValidationError ExecutedProccess(const TokenGroup& TokenGroupValidate){
  //Seleccionamos el tope del token group debido a que solo deberia haber uno no habra problema
  Token CommandSelect = TokenGroupValidate.command.front();
  const CommandMetaData* Command = FindCommand(CommandSelect.name);

  if(!Command->handler(CommandSelect.name)){
    std::cerr << "Comando " << CommandSelect.name << "no implementado por el momento\n";
    return ValidationError::CommandNotImplemented;
  }

  Command->handler(CommandSelect.name);

  return ValidationError::AllCorrect;
}
