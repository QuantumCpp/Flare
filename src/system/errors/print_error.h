#pragma once
#include "../../system/types/DataError.h"

void PrintDetailGenericError(const DataErrorDetail* ErrorDetail , const std::string& DetailInput , const std::vector<std::string>& DetailError);

void PrintCommandNotImplementedError(const DataErrorDetail* ErrorDetail, const std::string& DetailInput , const std::vector<std::string>& DetailError);


void PrintCommandNotFoundError(const DataErrorDetail* ErrorDetail, const std::string& DetailInput , const std::vector<std::string>& DetailError);

void PrintCommandIncorrectPositionError(const DataErrorDetail* ErrorDetail, const std::string& DetailInput , const std::vector<std::string>& DetailError);

void PrintOptionNotFoundError(const DataErrorDetail* ErrorDetail, const std::string& DetailInput, const std::vector<std::string>& DetailError);

void PrintPathNotExistError(const DataErrorDetail* ErrorDetail, const std::string& DetailInput, const std::vector<std::string>& DetailError);
