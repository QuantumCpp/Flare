#include "../PipelineProcees/ProccesOfClasification/ProceesOfClasification.h"

int main(){

  TokenGroup tokenGP;
  std::vector<Token> token;

  token.emplace_back(Token{TypeToken::Command, "list", ""});
  token.emplace_back(Token{TypeToken::Option, "--extension", ".docx"});
  token.emplace_back(Token{TypeToken::Command, "-e", ""});
  token.emplace_back(Token{TypeToken::Option, "hola", ""});

  if(ClasificationDataToken(token, tokenGP).Error == ValidationError::AllCorrect){
    std::cout<<"Todo correcto\n";
  }
  else{
    std::cout<< ClasificationDataToken(token,tokenGP).SpecificError;
  }

  return 0;
}
