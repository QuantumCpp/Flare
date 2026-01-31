#include "PrintErrorDetail.h"
#include <iostream>

void PrintDetailGenericError(const DataErrorDetail* ErrorDetail){
  std::cerr<< "Error [" << ErrorDetail->NameError << "] " << ErrorDetail->ShortDetail << "\n";
}
