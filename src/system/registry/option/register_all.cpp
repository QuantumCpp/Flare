#include "register_all.h"
#include "../option/option_registry.h"
#include "../../types/OptionMetaData.h"
#include "../../types/ValuePolicy.h"
#include "../../types/ValueType.h"
#include "../../types/OptionContex.h"
#include "../../../commands/list/handlers/filter_hanlder.cpp"
#include <variant>

void RegisterAllOptions() {
  
  //Recurisve se trabaja directamente en la funcion, no tiene un metodo propio
  OptionMetaData recursive;
  recursive.names = {"-r", "--recursive"};
  recursive.description = "Lista subdirectorios recursivamente";
  recursive.value_policy = ValuePolicy::None;
  recursive.value_type = ValueType::None;
  recursive.default_name = "--recursive";
  recursive.process_type = OptionProcessType::modifier;
  recursive.handler = std::monostate{};

  RegisterOption(recursive);
  
  //all por si misma no tiene un metodo
  OptionMetaData all;
  all.names = {"-a", "--all"};
  all.description = "Muestra archivos ocultos (que empiezan con .)";
  all.value_policy = ValuePolicy::None;
  all.value_type = ValueType::None;
  all.default_name = "--all";
  all.conflicts_with = {"--extension"};
  all.process_type = OptionProcessType::filter;
  all.handler = std::monostate{};
  RegisterOption(all);

  OptionMetaData extension;
  extension.names = {"-e", "--extension"};
  extension.description = "Filtra archivos por extensión";
  extension.value_policy = ValuePolicy::Required;
  extension.value_type = ValueType::String;
  extension.default_name = "--extension";
  extension.conflicts_with = {"--all"};
  extension.process_type = OptionProcessType::filter;
  extension.handler = FilterHandler(FilterByExtension);
  RegisterOption(extension);

  OptionMetaData min_size;
  min_size.names = {"-s", "--min-size"};
  min_size.description = "Filtra archivos con tamaño mínimo";
  min_size.value_policy = ValuePolicy::Required;
  min_size.value_type = ValueType::Size;
  min_size.default_name = "--min-size";
  min_size.process_type = OptionProcessType::filter;
  min_size.handler = FilterHandler(FilterByMinSize);
  RegisterOption(min_size);

  OptionMetaData max_size;
  max_size.names = {"--max-size"};
  max_size.description = "Filtra archivos con tamaño máximo";
  max_size.value_policy = ValuePolicy::Required;
  max_size.value_type = ValueType::Size;
  max_size.default_name = "--max-size";
  max_size.process_type = OptionProcessType::filter;
  max_size.handler = FilterHandler(FilterByMaxSize);

  RegisterOption(max_size);

  OptionMetaData after_date;
  after_date.names = {"-d", "--after-date"};
  after_date.description = "Filtra archivos modificados después de esta fecha";
  after_date.value_policy = ValuePolicy::Required;
  after_date.value_type = ValueType::Date;
  after_date.default_name = "--after-date";
  after_date.process_type = OptionProcessType::filter;
  after_date.handler = FilterHandler(FilterByAfterDate);

  RegisterOption(after_date);

  OptionMetaData before_date;
  before_date.names = {"--before-date"};
  before_date.description = "Filtra archivos modificados antes de esta fecha";
  before_date.value_policy = ValuePolicy::Required;
  before_date.value_type = ValueType::Date;
  before_date.default_name = "--before-date";
  before_date.process_type = OptionProcessType::filter;
  before_date.handler = FilterHandler(FilterByBeforeDate);

  RegisterOption(before_date);

  OptionMetaData sortBy;
  sortBy.names = {"--sort-by"};
  sortBy.description = "Ordena resultados por nombre, tamaño o fecha";
  sortBy.value_policy = ValuePolicy::Required;
  //sortBy.value_type = ValueType::;
  sortBy.default_name = "--sort-by";
  RegisterOption(sortBy);

  OptionMetaData reverse;
  reverse.names = {"--reverse"};
  reverse.description = "Invierte el orden de los resultados";
  reverse.value_policy = ValuePolicy::None;
  reverse.value_type = ValueType::None;
  reverse.default_name = "--reverse";
  reverse.requieres = {"--sort-by"};
  reverse.process_type = OptionProcessType::modifier;
  reverse.handler = std::monostate{};
  RegisterOption(reverse);

  OptionMetaData longFormat;
  longFormat.names = {"-l", "--long"};
  longFormat.description = "Formato detallado (nombre, tamaño, fecha, permisos)";
  longFormat.value_policy = ValuePolicy::None;
  longFormat.value_type = ValueType::None;
  longFormat.default_name = "--long";
  longFormat.conflicts_with = {"--simple"};
  RegisterOption(longFormat);

  OptionMetaData simpleFormat;
  simpleFormat.names = {"--simple"};
  simpleFormat.description = "Solo muestra nombres de archivo";
  simpleFormat.value_policy = ValuePolicy::None;
  simpleFormat.value_type = ValueType::None;
  simpleFormat.default_name = "--simple";
  simpleFormat.conflicts_with = {"--long"};
  RegisterOption(simpleFormat);
}

