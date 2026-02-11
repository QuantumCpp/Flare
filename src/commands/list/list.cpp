#include "list.h"
#include <algorithm>
#include <cctype>
#include <functional>
#include <string>
#include <filesystem>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <iostream>
#include <ranges>
#include <chrono>
#include "../../system/types/DataError.h"
#include "../../system/registry/error/error_registry.h"
#include "../../system/types/Token.h"
#include "../../system/types/TokenGroup.h"
#include "../../system/types/ValidationError.h"
#include "system/registry/option/option_registry.h"
#include "system/types/OptionContex.h"
#include "system/types/OptionMetaData.h"
#include "system/types/TypeToken.h"
#include <format>

namespace {
  
  void OrderedDirectoryItems(std::vector<std::filesystem::directory_entry>& FilesDirectory){
    std::ranges::sort(FilesDirectory, [](const auto& first, const auto& second){
      auto to_lower = [](char cha){return std::tolower(static_cast<unsigned char>(cha));};
      auto first_name = first.path().filename().string() | std::views::transform(to_lower);
      auto second_name = second.path().filename().string() | std::views::transform(to_lower);
      return std::ranges::lexicographical_compare(first_name, second_name);
    });
  }

  //Extraer del container los nombres de las opciones introducidas por el usuario para facilidad de busqueda posterior
  std::unordered_set<std::string> ExtractOptionName(const std::vector<Token>& container_token_option){ 
    std::unordered_set<std::string> container_option_name;
    container_option_name.reserve(container_option_name.size());
    for(const auto& archive_name : container_token_option){
      container_option_name.insert(archive_name.name);
    }
    return container_option_name;
  }
  
  //Extraer los nombres de los directorios y validarlos
  std::vector<std::string> ExtractAndValidateDirectory(const std::vector<Token>& container_token_positional){
    std::vector<std::string> container_positional_name;
    if(!container_token_positional.empty()){
      for(const auto& entry : container_token_positional){
        std::filesystem::path path = entry.name;
        if(std::filesystem::exists(path) && std::filesystem::is_directory(path)){
          container_positional_name.emplace_back(entry.name);
        }
        else{
           const DataErrorDetail* ErrorSucess = GetError(ValidationError::PathDoesNotExist);
           ErrorSucess->handler(ErrorSucess, path, std::vector<std::string>{}); 
        }
      }
    }
    else{
      std::filesystem::path path = std::filesystem::current_path();
      container_positional_name.emplace_back(path.filename().string());
    }

    return container_positional_name;
  }

  //Extraer los archivos dentro de un directorio X (recursivo o no)
  std::vector<std::filesystem::directory_entry> ExtractFilesDirectory(const std::filesystem::path& path, 
      const bool recursive_active){
    std::vector<std::filesystem::directory_entry> archive_directory;
    
    try{
      if(recursive_active){
        for(const auto& dir_entry : std::filesystem::recursive_directory_iterator(path)){
          archive_directory.emplace_back(dir_entry);
        }
      }
      else{
        for(const auto& dir_entry : std::filesystem::directory_iterator(path)){
          archive_directory.emplace_back(dir_entry);
        }
      }
    }
    catch (const std::filesystem::filesystem_error& error){
        std::cerr << "c-files ERROR [" << error.what() << "] \n";
    }
    OrderedDirectoryItems(archive_directory);
    return archive_directory;
  }

  bool PrintInformation(bool long_format, const std::vector<std::string>& container_directory_name, 
      std::unordered_map<std::string,std::vector<std::filesystem::directory_entry>>& map_entry_directory){
    
    for(const auto& directory_name : container_directory_name){
      std::cout << std::format("\n{}/ :\n",directory_name);
      if(map_entry_directory.contains(directory_name)){
        std::cout << std::format("{:=<70}\n", "");
        if(long_format){
          std::cout << std::format("{:<40} {:>10} {:>8} {}\n", 
             "NAME" , "SIZE" , "TYPE" , "MODIFIED");
          std::cout << std::format("{:-<70}\n", "");
          for(const auto& file : map_entry_directory[directory_name]){
              auto filename = file.path().relative_path().filename().string();
              auto size_file = std::filesystem::is_regular_file(file) ? file.file_size() : 0;
              std::string type_file = std::filesystem::is_directory(file) ? "DIR" : "FILE";
            
              auto last_file_modification = std::filesystem::last_write_time(file);
              auto stcp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
                  last_file_modification - std::filesystem::file_time_type::clock::now() + 
                    std::chrono::system_clock::now()
                  );
              auto cftime = std::chrono::system_clock::to_time_t(stcp);

              std::cout << std::format(" {:<40} {:>10} {:>8} {:%Y-%d-%m}\n",
                filename,
                size_file,
                type_file,
                std::chrono::system_clock::from_time_t(cftime));
          }
        }
        else{
          std::cout << std::format("{:<40} {:>10}\n" , "NAME", "TYPE");
          std::cout << std::format("{:-<70}\n","");
          for(const auto& file : map_entry_directory[directory_name]){
            auto file_name = file.path().filename().string();
            std::string type_file = std::filesystem::is_directory(file) ? "DIR" : "FILE";
            std::cout << std::format("{:<40} {:>10}\n", file_name, type_file);
          }
        }
      }
    }
    return true;
  }
}


bool CommandList(const TokenGroup &token_group_raw){
  
  std::unordered_set<std::string> option_exist;
  std::vector<Token> container_token_positional = token_group_raw.positional;
  if(token_group_raw.positional.empty()){
    container_token_positional.emplace_back(Token{.type = TypeToken::Positional,
                                                  .name = std::string("."),
                                                  .value = ""}); 
  }
  option_exist = ExtractOptionName(token_group_raw.option);

  //obtener los nombres de los directorios y validar su existencia 
  std::vector<std::string> container_directory_name = ExtractAndValidateDirectory(container_token_positional);
  std::unordered_map<std::string,std::vector<std::filesystem::directory_entry>> map_entry_directory;

  for(const auto& file : container_directory_name){
    std::filesystem::path path = file;
    map_entry_directory[file] = ExtractFilesDirectory(path, option_exist.contains("--recursive"));
  }
  
  //aplicar filtros
  for(const auto& opcion_filtro : token_group_raw.option){
    const OptionMetaData* Option_handler_filter = FindOption(opcion_filtro.name);
    if(Option_handler_filter->process_type != OptionProcessType::filter){
      continue;
    }
    for(const auto& file : container_directory_name){
      const auto& filter_func = std::get<FilterHandler>(Option_handler_filter->handler);
      FilterContext ctx{map_entry_directory[file] , opcion_filtro.value};
      std::vector<std::filesystem::directory_entry> new_entry = filter_func(ctx);
      map_entry_directory[file] = std::move(new_entry);
    }
  }

  PrintInformation(option_exist.contains("--long"),container_directory_name, map_entry_directory);  

  return true;
}

