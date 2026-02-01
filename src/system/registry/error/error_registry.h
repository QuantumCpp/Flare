#pragma once
#include "../../types/DataError.h"

void RegisterError(const DataErrorDetail& error);
const DataErrorDetail* GetError(const ValidationError& Id);
