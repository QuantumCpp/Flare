#pragma once
#include <vector>
#include "../../system/types/ValidationError.h"
#include "../../system/types/Token.h"
#include "../../system/types/TokenGroup.h"


bool ClasificationDataToken(const std::vector<Token>& tokens, TokenGroup& GpToken);
