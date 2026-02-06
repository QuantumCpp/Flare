#include "../../../system/types/OptionContex.h"
#include "../../../system/types/OptionProcessType.h"
#include <filesystem>
#include <any>
#include <string>
#include <cstdint>

//Proceso de filtrado por extension - espera un valor parecido a : .[extension]
bool FilterByExtension(const FilterContext& context_filter){
  
  if(const auto* extension = std::any_cast<std::string>(&context_filter.filter)){
    auto entry_ext = context_filter.entry.path().filename().string();
    return entry_ext == *extension;
  }
  return true;

}

bool FilterByMinSize(const FilterContext& context_filter){
  if(const int* min_size = std::any_cast<int>(&context_filter.filter)){
    if(!std::filesystem::is_directory(context_filter.entry)){
      auto size_file = std::filesystem::file_size(context_filter.entry);
      return size_file >= static_cast<std::uintmax_t>(*min_size);
    }
  }
  return true;
}

bool FilterByMaxSize(const FilterContext& context_filter){
  if(const int* max_size = std::any_cast<int>(&context_filter.filter)){
    if(!std::filesystem::is_directory(context_filter.entry)){
      auto size_file = std::filesystem::file_size(context_filter.entry);
      return size_file <= static_cast<std::uintmax_t>(*max_size);
    }
  }
  return true;
}

bool FilterPointHidden(const FilterContext& context_filter){
  const auto begin = context_filter.entry.path().filename().string();
  return begin.starts_with(".");
}

bool FilterByAfterDate(const FilterContext& context_filter){
  
  return true;
}

bool FilterByBeforeDate(const FilterContext& context_filter){
  return true;
}



