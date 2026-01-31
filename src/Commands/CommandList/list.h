#pragma once
#include "../../SystemUtilites/GeneralLibraries/GeneralLibraries.h"
#include "../../SystemUtilites/Structs/Token.h"
#include "../../SystemUtilites/Structs/TokenGroup.h"
#include "../../SystemUtilites/EnumsClass/ValidationError.h"

ValidationError CommandList(const TokenGroup& TokenGroupRaw);

