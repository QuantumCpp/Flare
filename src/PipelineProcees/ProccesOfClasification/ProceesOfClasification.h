#pragma once
#include "../../SystemUtilites/GeneralLibraries/GeneralLibraries.h"
#include "../../SystemUtilites/Structs/Token.h"
#include "../../SystemUtilites/Structs/DataError.h"
#include "../../SystemUtilites/Structs/TokenGroup.h"
#include "../../SystemUtilites/OptionRegistry/OptionRegistry.h"
#include "../../SystemUtilites/CommandRegister/CommandRegister.h"
#include "../../Utils/IsValidatedDate/IsValidatedDate.h"

ValidationError ClasificationDataToken(const std::vector<Token>& tokens, TokenGroup& GpToken);
