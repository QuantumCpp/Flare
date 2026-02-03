#include "execution.h"
#include "../../system/types/CommandMetaData.h"
#include "../../system/registry/command/command_registry.h"
#include "../../system/registry/error/error_registry.h"

bool ExecutedProccess(const TokenGroup& TokenGroupValidate){
  //Seleccionamos el tope del token group debido a que solo deberia haber uno no habra problema
  Token CommandSelect = TokenGroupValidate.command.front();
  const CommandMetaData* Command = FindCommand(CommandSelect.name);
  const DataErrorDetail* ErrorSucess;

  if(!Command->handler(CommandSelect.name)){
    ErrorSucess = GetError(ValidationError::CommandNotImplemented);
    ErrorSucess->handler(ErrorSucess);
    return false;
  }

  Command->handler(CommandSelect.name);

  return true;
}
