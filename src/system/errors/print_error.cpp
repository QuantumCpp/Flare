#include "print_error.h"
#include <iostream>
#include <ostream>

void PrintDetailGenericError(const DataErrorDetail* ErrorDetail , const std::string& DetailInput , const std::vector<std::string>& DetailError){
  std::cerr<< "c-files Error : " << ErrorDetail->ShortDetail << std::endl;
}

void PrintCommandNotImplementedError(const DataErrorDetail* ErrorDetail, const std::string& DetailInput , const std::vector<std::string>& DetailError){
  std::cerr << "c-files ERROR : Command [" << DetailInput << "] not implemented\n";
} 


void PrintCommandNotFoundError(const DataErrorDetail* ErrorDetail, const std::string& DetailInput , const std::vector<std::string>& DetailError){
  std::cerr << "c-files ERROR : Command [" << DetailInput << "] not found\n";
}

void PrintCommandIncorrectPositionError(const DataErrorDetail* ErrorDetail, const std::string& DetailInput , const std::vector<std::string>& DetailError){
  std::cerr << "c-files ERROR : Command in incorrect position\n";
}

void PrintOptionNotFoundError(const DataErrorDetail* ErrorDetail, const std::string& DetailInput, const std::vector<std::string>& DetailError){
  std::cerr << "c-files ERROR : option [" << DetailInput << "] not found\n";
}

void PrintPathNotExistError(const DataErrorDetail* ErrorDetail, const std::string& DetailInput, const std::vector<std::string>& DetailError){
   std::cerr << "c-files [ERROR] : Directory [" << DetailInput << "] not exist\n";
}

