#include "error_registry.h"

static std::unordered_map<ValidationError, DataErrorDetail> ErrorTable;

void RegisterError(const DataErrorDetail& error){
  ErrorTable[error.ErrorID] = error;
}

const DataErrorDetail* GetError(const ValidationError& Id ){
  auto it = ErrorTable.find(Id);

  if(it == ErrorTable.end()){
    return nullptr;
  }

  return &it->second;

}
