#include "register_all.h"
#include "../option/option_registry.h"
#include "../../types/OptionMetaData.h"
#include "../../types/ValuePolicy.h"
#include "../../types/ValueType.h"
#include "../../types/OptionContex.h"

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

  RegisterOption(extension);

  OptionMetaData minSize;
  minSize.names = {"-s", "--min-size"};
  minSize.description = "Filtra archivos con tamaño mínimo";
  minSize.value_policy = ValuePolicy::Required;
  minSize.value_type = ValueType::Integer;
  minSize.default_name = "--min-size";
  RegisterOption(minSize);

  OptionMetaData maxSize;
  maxSize.names = {"--max-size"};
  maxSize.description = "Filtra archivos con tamaño máximo";
  maxSize.value_policy = ValuePolicy::Required;
  maxSize.value_type = ValueType::Integer;
  maxSize.default_name = "--max-size";
  RegisterOption(maxSize);

  OptionMetaData afterDate;
  afterDate.names = {"-d", "--after-date"};
  afterDate.description = "Filtra archivos modificados después de esta fecha";
  afterDate.value_policy = ValuePolicy::Required;
  afterDate.value_type = ValueType::Date;
  afterDate.default_name = "--after-date";
  RegisterOption(afterDate);

  OptionMetaData beforeDate;
  beforeDate.names = {"--before-date"};
  beforeDate.description = "Filtra archivos modificados antes de esta fecha";
  beforeDate.value_policy = ValuePolicy::Required;
  beforeDate.value_type = ValueType::Date;
  beforeDate.default_name = "--before-date";
  RegisterOption(beforeDate);

  OptionMetaData sortBy;
  sortBy.names = {"--sort-by"};
  sortBy.description = "Ordena resultados por nombre, tamaño o fecha";
  sortBy.value_policy = ValuePolicy::Required;
  sortBy.value_type = ValueType::Enum;
  sortBy.default_name = "--sort-by";
  RegisterOption(sortBy);

  OptionMetaData reverse;
  reverse.names = {"--reverse"};
  reverse.description = "Invierte el orden de los resultados";
  reverse.value_policy = ValuePolicy::None;
  reverse.value_type = ValueType::None;
  reverse.default_name = "--reverse";
  reverse.requieres = {"--sort-by"};
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

