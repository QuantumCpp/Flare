#include "../../../system/types/OptionContex.h"
#include "../../../system/types/OptionProcessType.h"
#include "../../../utils/ParseStringDate.cpp"
#include <cctype>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <filesystem>
#include <vector>
#include <any>
#include <string>
#include <cstdint>
#include <ranges>

std::vector<std::filesystem::directory_entry> FilterByExtension(const FilterContext& context_filter){
  const auto* filter_extension = std::any_cast<std::string>(&context_filter.filter);
  if(filter_extension == nullptr || !filter_extension->starts_with(".")){
    return {};
  }

  auto container_filter_extension = context_filter.entry | std::views::filter([&filter_extension](const auto& entry){
        return entry.is_directory() || entry.path().extension() == *filter_extension; 
      }); 

  return {container_filter_extension.begin() , container_filter_extension.end()};
}

std::vector<std::filesystem::directory_entry> FilterByMinSize(const FilterContext& context_filter){
  const auto* min_size_string = std::any_cast<std::string>(&context_filter.filter);
  std::uintmax_t min_size_complete;
  
  std::string number;
  int multiplicador = 1;
  const int kilobyte = 1024;
  for(const auto& numb : *min_size_string){
    if(isdigit(numb) != 0){
      number+=numb;      
    }
  }
  
  if(min_size_string->ends_with("KB")){
    multiplicador = kilobyte;
  }
  else if(min_size_string->ends_with("MB")){
    multiplicador = static_cast<int>(std::pow(kilobyte,2));
  }
  else if(min_size_string->ends_with("GB")){
    multiplicador = static_cast<int>(std::pow(kilobyte,3));
  }
  else if(min_size_string->ends_with("TB")){
    multiplicador = static_cast<int>(std::pow(kilobyte,4));
  }
  
  min_size_complete = static_cast<std::uintmax_t>(std::stoi(number) * multiplicador);

  auto container_filter_size = context_filter.entry | std::views::filter([&min_size_complete] (const auto& entry){
        return entry.is_directory() || entry.file_size() >= min_size_complete;
      });
  return {container_filter_size.begin(), container_filter_size.end()};
}

std::vector<std::filesystem::directory_entry> FilterByMaxSize(const FilterContext& context_filter){

   const auto* min_size_string = std::any_cast<std::string>(&context_filter.filter);
  std::uintmax_t min_size_complete;
  
  std::string number;
  int multiplicador = 1;
  const int kilobyte = 1024;
  for(const auto& numb : *min_size_string){
    if(isdigit(numb) != 0){
      number+=numb;      
    }
  }
  
  if(min_size_string->ends_with("KB")){
    multiplicador = kilobyte;
  }
  else if(min_size_string->ends_with("MB")){
    multiplicador = static_cast<int>(std::pow(kilobyte,2));
  }
  else if(min_size_string->ends_with("GB")){
    multiplicador = static_cast<int>(std::pow(kilobyte,3));
  }
  else if(min_size_string->ends_with("TB")){
    multiplicador = static_cast<int>(std::pow(kilobyte,4));
  }
  
  min_size_complete = static_cast<std::uintmax_t>(std::stoi(number) * multiplicador);

  auto container_filter_size = context_filter.entry | std::views::filter([&min_size_complete] (const auto& entry){
        return entry.is_directory() || entry.file_size() <= min_size_complete;
      });
  return {container_filter_size.begin(), container_filter_size.end()};

}

std::vector<std::filesystem::directory_entry> FilterPointHidden(const FilterContext& context_filter){
  auto container_without_point = context_filter.entry | std::views::filter([] (const auto& entry){
      return !entry.path().filename().string().starts_with(".");
      });
  return {container_without_point.begin() , container_without_point.end()};
}

std::vector<std::filesystem::directory_entry> FilterByAfterDate(const FilterContext& context_filter){  
  //convertir fecha del archivo en sytem::clock en presicio nde dias
  const auto* string_date = std::any_cast<std::string>(&context_filter.filter);
  auto filter_date = ParseStringDate(*string_date);
  
  auto container_filter_after_date = context_filter.entry | std::views::filter([&filter_date](const auto& entry){
        if(entry.is_directory()){
          return true;
        }
        auto file_date = std::chrono::clock_cast<std::chrono::system_clock>(entry.last_write_time());
        auto file_date_days = std::chrono::time_point_cast<std::chrono::days>(file_date);
        return file_date_days >= filter_date;
      });
  return {container_filter_after_date.begin() , container_filter_after_date.end()};
}
std::vector<std::filesystem::directory_entry> FilterByBeforeDate(const FilterContext& context_filter){
  //convertir fecha del archivo en sytem::clock en presicio nde dias
  const auto* string_date = std::any_cast<std::string>(&context_filter.filter);
  auto filter_date = ParseStringDate(*string_date);
  
  auto container_filter_before_date = context_filter.entry | std::views::filter([&filter_date](const auto& entry){
        if(entry.is_directory()){
          return true;
        }
        auto file_date = std::chrono::clock_cast<std::chrono::system_clock>(entry.last_write_time());
        auto file_date_days = std::chrono::time_point_cast<std::chrono::days>(file_date);
        return file_date_days <= filter_date;
      });
  return {container_filter_before_date.begin() , container_filter_before_date.end()};
}



