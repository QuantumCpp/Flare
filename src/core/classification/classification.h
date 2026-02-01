#pragma once
#include <vector>
#include "../../system/types/ValidationError.h"
#include "../../system/types/Token.h"
#include "../../system/types/TokenGroup.h"


ValidationError ClasificationDataToken(const std::vector<Token>& tokens, TokenGroup& GpToken);
