#include "register_all.h"
#include "../../types/CommandMetaData.h"
#include "../../registry/option/option_registry.h"
#include "../../registry/command/command_registry.h"
#include "../../../commands/list/list.h"

void RegisterAllCommand(){
  //Comando list 
  CommandMetaData list;
  list.name = "list";
  list.description = "Listar carpetas y documentos de una ruta en espefico";
  list.usage_example = {"c-files list .", "c-files list /Downloads"};
  list.options["--extension"] = FindOption("--extension");
  list.options["--recursive"] = FindOption("--recursive");
  list.options["--all"] = FindOption("--all");
  list.options["--min-size"] = FindOption("--min-size");
  list.options["--max-size"] = FindOption("--max-size");
  list.options["--before-date"] = FindOption("--before-date");
  list.options["--after-date"] = FindOption("--after-date");
  list.options["--sort-by"] = FindOption("--sort-by");
  list.options["--reverse"] = FindOption("--reverse");
  list.options["--long"] = FindOption("--long");
  list.options["--simple"] = FindOption("--simple");
  list.value_policy = ValuePolicy::Optional;
  list.handler = CommandList;

  CommandRegister(list);

}
