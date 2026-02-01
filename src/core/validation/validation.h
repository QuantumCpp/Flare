#pragma once
#include "../../system/types/ValidationError.h"
#include <vector>
#include "../../system/types/TokenGroup.h"

ValidationError ValidationDataToken(TokenGroup& TokenGroupRaw);
