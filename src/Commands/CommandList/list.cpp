#include "list.h"

ValidationError CommandList(const TokenGroup &TokenGroupRaw){
  
  std::vector<Token> TokenOption = TokenGroupRaw.option;
  std::unordered_set<std::string> OptionFind;
  std::vector<Token> TokenPositional = TokenGroupRaw.positional;
  std::filesystem::path path = std::filesystem::current_path();  

  //Listar elementos de una carpeta sin opciones anadidas
  if(TokenOption.empty() && !TokenPositional.empty()){
    
    //Primer recorrido sobre el vector de Posicionales para ver si lo introducido es una carpeta real
    long unsigned int NumberDirectoryNotExist = 0;
    for(const auto& file : TokenPositional){
      path = file.name;
      if(!std::filesystem::directory_entry(path).exists()){
        NumberDirectoryNotExist ++;
        std::cerr << "c-files [ERROR] : Directory [" << file.name << "] not exist\n";
      }
      else{
        //En caso de existir imprimira la el nombre en formato tabla de los elemento del directorio elegido 
        std::cout << "Directory: " << file.name << "\n";
        for(const auto& FileDirectory : std::filesystem::directory_iterator(path) ){
          std::cout << FileDirectory.path() << "\n";
        }
      }
       
    }
    //Retoron de error en caso de que el numero de carpetas inexistentes sea igual al de lo introducido en el positional 
    if(NumberDirectoryNotExist == TokenPositional.size()){
      return ValidationError::PathDoesNotExist;
    }
  }

  return ValidationError::AllCorrect;
}
