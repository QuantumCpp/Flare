#include "validation.h"
#include "../../system/types/OptionMetaData.h"
#include "../../system/types/CommandMetaData.h"
#include "../../system/registry/command/command_registry.h"
#include "../../system/registry/option/option_registry.h"
#include "../../system/registry/error/error_registry.h"
#include "../../utils/date_validator.h"
#include "system/types/ValidationError.h"
#include <algorithm>
#include <charconv>
#include <unordered_set>
#include <vector>
#include <string>
#include <ranges>
#include "../../system/types/Token.h"
#include "../../system/types/TokenGroup.h"
#include "../../system/types/DataError.h"
#include "../../system/types/ValidationError.h"
#include "../../system/types/ValueType.h"
#include "../../system/types/ValuePolicy.h"

/*
 Por convencion semantica las opciones largas (o cortas) con valor deben darse de la forma
 -e=.docx o --extension=.docx sera invalido sucesos como -e .docx o --extension .docx
 Esto para simplificar las logicas de validaciones y hacer comandos y desiciones mas
 declarativas y legibles.
*/

bool ValidationTypeValueCorrect(const OptionMetaData* OptionData,
                                const Token& OptionToken,
                                const DataErrorDetail* ErrorDetail);

bool IsInteger(const std::string& str);
bool IsFloat(const std::string& str);

bool ValidationDataToken(TokenGroup& TokenGroupRaw) {

    auto const& GroupCommandToken = TokenGroupRaw.command;
    auto const& GroupOptionToken = TokenGroupRaw.option;

    const CommandMetaData* CommandData;
    const OptionMetaData* OptionData;
    const DataErrorDetail* ErrorData = nullptr;

    CommandData = FindCommand(GroupCommandToken.front().name);
    
    std::unordered_set<std::string> TotalOptionAvaible;
    for(const auto& option : GroupOptionToken){
      TotalOptionAvaible.insert(option.name);
    }

    for (size_t i = 0; i < GroupOptionToken.size(); i++) {

        auto const& OptionToken = GroupOptionToken[i];
        OptionData = FindOption(OptionToken.name);

        if (OptionData == nullptr) {
            ErrorData = GetError(ValidationError::OptionNotFound);
            ErrorData->handler(ErrorData, OptionData->default_name,std::vector<std::string>{""});
            return false;
        }

        if (!CommandData->options.contains(OptionToken.name)) {
            ErrorData = GetError(ValidationError::OptionForWrongCommand);
            ErrorData->handler(ErrorData, CommandData->name,std::vector<std::string>{OptionToken.name});
            return false;
        }

        for (size_t j = i + 1; j < GroupOptionToken.size(); j++) {
            Token ConflictToken = GroupOptionToken[j];

            for (const auto& ElementConflict : OptionData->conflicts_with) {
                if (ConflictToken.name == ElementConflict) {
                    ErrorData = GetError(ValidationError::ConflictingOptions);
                    ErrorData->handler(ErrorData,OptionData->default_name,std::vector<std::string>{ConflictToken.name});
                    return false;
                }
            }
        }

        if (OptionData->value_policy == ValuePolicy::Required) {
            if (OptionToken.value == "") {
                ErrorData = GetError(ValidationError::OptionRequiresValue);
                ErrorData->handler(ErrorData,OptionData->default_name,std::vector<std::string>{""});
                return false;
            }
        }

        if (OptionData->value_policy == ValuePolicy::None) {
            if (OptionToken.value != "") {
                ErrorData = GetError(ValidationError::OptionDoesNotAcceptValue);
                ErrorData->handler(ErrorData,OptionData->default_name,std::vector<std::string>{OptionToken.name});
                return false;
            }
        }

        if (!OptionData->requieres.empty()) {

            const auto its = std::ranges::find_if(OptionData->requieres,[&] (const std::string& option){
                return !TotalOptionAvaible.contains(option);
                });

            if(its != OptionData->requieres.end()){
              ErrorData = GetError(ValidationError::MissingRequiredOption);
              ErrorData->handler(ErrorData, OptionToken.name , std::vector<std::string>{*its});
              return false;
            }
        }

        if (OptionToken.value != "") {
          bool Validate_all = !ValidationTypeValueCorrect(OptionData, OptionToken, ErrorData); 
            if(!Validate_all){
              return false;
            }
        }
    }

    return true;
}

/*
 Solo se hacen validaciones para enteros, flotantes y fechas debido a que todo se introduce en string,
 no tendria sentido analizar si es string, los path pueden ser de formato absoluto o relativo asi que
 se deja esa validacion del string a la hora de usar la opcion.
 El date lo analizo porque si deben de seguir un formato YYYY-MM-DD
*/

bool ValidationTypeValueCorrect(const OptionMetaData* OptionData,
                                const Token& OptionToken,
                                const DataErrorDetail* ErrorDetail) {

    switch (OptionData->value_type) {

        case ValueType::None:
          return true;
          break;

        case ValueType::Enum:
          return true;
          break;

        case ValueType::Path:
          return true;
          break;

        case ValueType::String:
          return true;
          break;

        case ValueType::Integer:
            if (!IsInteger(OptionToken.value)) {
                ErrorDetail = GetError(ValidationError::InvalidValueType_Integer);
                ErrorDetail->handler(ErrorDetail,
                                     OptionToken.name,
                                     std::vector<std::string>{""});
            }
            return false;
            break;

        case ValueType::Float:
            if (!IsFloat(OptionToken.value)) {
                ErrorDetail = GetError(ValidationError::InvalidValueType_Float);
                ErrorDetail->handler(ErrorDetail,
                                     OptionToken.name,
                                     std::vector<std::string>{""});
            }
            return false;
            break;

        case ValueType::Date:
            if (!isValidatedDate(OptionToken.value)) {
                ErrorDetail = GetError(ValidationError::InvalidValueType_Date);
                ErrorDetail->handler(ErrorDetail,
                                     OptionToken.name,
                                     std::vector<std::string>{OptionToken.value});
            }

            if (!isValidateContexDate(OptionToken.value)) {
                ErrorDetail = GetError(ValidationError::InvalidValueType_Date);
                ErrorDetail->handler(ErrorDetail,
                                     OptionToken.name,
                                     std::vector<std::string>{OptionToken.value});
            }
            return false;
            break;

        default:
            return true;;
    }
    return true;
}

bool IsInteger(const std::string& str) {
    int value;
    auto conversion = std::from_chars(str.data(),
                                      str.data() + str.size(),
                                      value);

    return conversion.ec == std::errc() &&
           conversion.ptr == str.data() + str.size();
}

bool IsFloat(const std::string& str) {
    float value;
    auto conversion = std::from_chars(str.data(),
                                      str.data() + str.size(),
                                      value);

    return conversion.ec == std::errc() &&
           conversion.ptr == str.data() + str.size();
}

