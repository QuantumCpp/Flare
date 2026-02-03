#include "list.h"
#include <algorithm>
#include <cctype>
#include <string>
#include <filesystem>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <iostream>
#include "../../system/types/DataError.h"
#include "../../system/registry/error/error_registry.h"

void OrderedDirectoryItems(std::vector<std::filesystem::directory_entry>& FilesDirectory){
  std::sort(FilesDirectory.begin(), FilesDirectory.end(), 
      [](const auto& a , const auto& b){
      auto sa = a.path().filename().string();
      auto sb = b.path().filename().string();
      std::transform(sa.begin(), sa.end() , sa.begin() , [](unsigned char c) {return std::tolower(c);});
      std::transform(sb.begin(), sb.end() , sb.begin() , [](unsigned char c) {return std::tolower(c);});

      return sa < sb;
      });
}

bool CommandList(const TokenGroup &TokenGroupRaw){
  
  std::vector<Token> TokenOption = TokenGroupRaw.option;
  std::unordered_set<std::string> OptionFind;
  std::vector<Token> TokenPositional = TokenGroupRaw.positional;
  std::filesystem::path path = std::filesystem::current_path();  
  const DataErrorDetail* ErrorSucess = nullptr;

  //Guardar los elementos option del TokenGroupRaw en un unordered_set
  for(const auto& file : TokenOption){
    OptionFind.insert(file.name);
  }

  bool recursive = OptionFind.count("--recursive") ? true : false;
  bool LongFormat = OptionFind.count("--long") ? true : false;

  std::vector<std::string> DirectoryName;
  std::unordered_map<std::string,std::vector<std::filesystem::directory_entry>> FilePath;
  
  //Si no hoy posicionales ignorar esto y dejar al path como current_path
  if(!TokenPositional.empty()){
    //Guardar y verificar que directorios en positional son validos
    for(const auto& Directory : TokenPositional){
      path = Directory.name;

      if(std::filesystem::exists(path) && std::filesystem::is_directory(path)){
        DirectoryName.emplace_back(Directory.name);
        std::vector<std::filesystem::directory_entry> FilesDirectory;

        for(const auto& file : std::filesystem::directory_iterator(path)){
          FilesDirectory.push_back(file);
        }
        OrderedDirectoryItems(FilesDirectory);
        FilePath[Directory.name] = FilesDirectory;
      }
      else{
        ErrorSucess = GetError(ValidationError::PathDoesNotExist);
        ErrorSucess->handler(ErrorSucess, path, std::vector<std::string>{});
      }
    }
  }
  else{
    DirectoryName.emplace_back(path.filename().string());
    std::vector<std::filesystem::directory_entry> FilesDirectory;
    for(const auto& file : std::filesystem::directory_iterator(path)){
      FilesDirectory.emplace_back(file);
    }
    OrderedDirectoryItems(FilesDirectory);
    FilePath[DirectoryName.front()] = FilesDirectory;
  }


  //proceso de filtrado de los directorios
  if(!TokenPositional.empty()){

  }

  for(const auto& Directory : DirectoryName){
    std::cout<< Directory << " :\n";
    auto it = FilePath.find(Directory);
    if(it != FilePath.end()){
      for(const auto & file : it->second){
        std::cout << std::filesystem::relative(file.path(),std::filesystem::current_path()).string() << std::endl;
      }
    }

    std::cout << "----------------------------\n";
  }

  return true;
}


