#include "../PipelineProcees/ProccesOfTokenization/ProccesOfTokenization.h"

#include "../PipelineProcees/ProccesOfTokenization/ProccesOfTokenization.h"
#include <cassert>
#include <iostream>

void TestTokenization(const std::vector<std::string>& argumentos, const std::string& testName) {
  std::cout << "\n=== " << testName << " ===\n";
  
  std::vector<Token> tokens = Tokenization(argumentos);

  // Prueba de impresión
  std::cout << "Tokens encontrados: " << tokens.size() << "\n";
  for(size_t i = 0; i < tokens.size(); i++) {
    const auto& elemento = tokens[i];
    std::cout << "[" << i << "] Token: " << elemento.name << "\n";
    std::cout << "    Tipo: ";
    if(elemento.type == TypeToken::Command) std::cout << "Comando\n";
    else if(elemento.type == TypeToken::Option) std::cout << "Opcion\n";
    else if(elemento.type == TypeToken::Positional) std::cout << "Posicional\n";
    else std::cout << "Desconocido\n";
    
    std::cout << "    Valor: " << elemento.value << "\n";
  }
  std::cout << "--- Fin de " << testName << " ---\n";
}

void RunAssertionTests() {
  std::cout << "\n=== PRUEBAS DE ASERCIÓN ===\n";
  
  // Test 1: Comando simple
  {
    std::vector<std::string> args = {"ls"};
    auto tokens = Tokenization(args);
    assert(tokens.size() == 1);
    assert(tokens[0].type == TypeToken::Command);
    assert(tokens[0].name == "ls");
    std::cout << "✓ Test comando simple pasado\n";
  }
  
  // Test 2: Opción corta sin valor
  {
    std::vector<std::string> args = {"ls", "-l"};
    auto tokens = Tokenization(args);
    assert(tokens.size() == 2);
    assert(tokens[0].type == TypeToken::Command);
    assert(tokens[1].type == TypeToken::Option);
    assert(tokens[1].name == "-l");
    std::cout << "✓ Test opción corta sin valor pasado\n";
  }
  
  // Test 3: Opción larga con valor
  {
    std::vector<std::string> args = {"grep", "--file=test.txt"};
    auto tokens = Tokenization(args);
    assert(tokens.size() == 2);
    assert(tokens[1].type == TypeToken::Option);
    assert(tokens[1].name == "--file");
    assert(tokens[1].value == "test.txt");
    std::cout << "✓ Test opción larga con valor pasado\n";
  }
  
  // Test 4: Múltiples opciones cortas combinadas
  {
    std::vector<std::string> args = {"tar", "-xzf"};
    auto tokens = Tokenization(args);
    assert(tokens.size() >= 2);
    std::cout << "✓ Test opciones combinadas pasado\n";
  }
  
  // Test 5: Separador --
  {
    std::vector<std::string> args = {"rm", "--", "-f", "archivo"};
    auto tokens = Tokenization(args);
    // Después de --, todo debería ser posicional
    bool foundSeparator = false;
    for(const auto& token : tokens) {
      if(token.name == "--") foundSeparator = true;
      if(foundSeparator && token.name != "--") {
        assert(token.type == TypeToken::Positional);
      }
    }
    std::cout << "✓ Test separador -- pasado\n";
  }
  
  // Test 6: Argumentos posicionales mixtos
  {
    std::vector<std::string> args = {"cp", "-r", "origen", "destino"};
    auto tokens = Tokenization(args);
    int positionalCount = 0;
    for(const auto& token : tokens) {
      if(token.type == TypeToken::Positional) positionalCount++;
    }
    assert(positionalCount == 2); // origen y destino
    std::cout << "✓ Test argumentos posicionales pasado\n";
  }
  
  std::cout << "✓ Todas las pruebas de aserción pasadas\n";
}

void RunComprehensiveTests() {
  std::cout << "\n=== PRUEBAS COMPREHENSIVAS ===\n";
  
  // Caso 1: IDEAL - Flujo normal
  std::vector<std::string> caso1 = {
    "list",
    "-opad",
    "-w",
    "--Opcion_larga",
    "--Opcion_larga=con_valor",
    "posicional"
  };
  TestTokenization(caso1, "Caso 1 - Flujo normal");
  
  // Caso 2: SEPARADOR - Con -- como separador
  std::vector<std::string> caso2 = {
    "list",
    "-opad",
    "--",
    "-w",
    "--Opcion_larga",
    "--Opcion_larga=con_valor",
    "posicional"
  };
  TestTokenization(caso2, "Caso 2 - Con separador --");
  
  // Caso 3: COMANDOS COMPLEJOS - Simulando find
  std::vector<std::string> caso3 = {
    "find",
    "/home/user",
    "-name",
    "*.txt",
    "-type",
    "f",
    "-exec",
    "grep",
    "-l",
    "hello",
    "{}",
    ";"
  };
  TestTokenization(caso3, "Caso 3 - Comando complejo (find)");
  
  // Caso 4: VALORES ESPECIALES - Con espacios y caracteres especiales
  std::vector<std::string> caso4 = {
    "echo",
    "--message=Hola Mundo",
    "-n",
    "--",
    "-esto_es_posicional",
    "otro posicional"
  };
  TestTokenization(caso4, "Caso 4 - Valores especiales");
  
  // Caso 5: OPCIONES ANIDADAS - Múltiples opciones cortas juntas
  std::vector<std::string> caso5 = {
    "tar",
    "-xzvf",
    "archivo.tar.gz",
    "-C",
    "/tmp",
    "--overwrite"
  };
  TestTokenization(caso5, "Caso 5 - Opciones anidadas (tar)");
  
  // Caso 6: SÓLO POSICIONALES
  std::vector<std::string> caso6 = {
    "cat",
    "file1.txt",
    "file2.txt",
    "file3.txt"
  };
  TestTokenization(caso6, "Caso 6 - Solo argumentos posicionales");
  
  // Caso 7: VACÍO Y BORDE
  std::vector<std::string> caso7 = {
    ""
  };
  TestTokenization(caso7, "Caso 7 - String vacío");
  
  // Caso 8: SÓLO OPCIONES
  std::vector<std::string> caso8 = {
    "--help",
    "-v",
    "--version"
  };
  TestTokenization(caso8, "Caso 8 - Solo opciones (sin comando)");
  
  // Caso 9: OPCIONES CON VALORES COMPLEJOS
  std::vector<std::string> caso9 = {
    "curl",
    "-X",
    "POST",
    "-H",
    "Content-Type: application/json",
    "-d",
    "{\"key\": \"value\"}",
    "https://api.example.com"
  };
  TestTokenization(caso9, "Caso 9 - Opciones con valores complejos (curl)");
}

void RunEdgeCaseTests() {
  std::cout << "\n=== PRUEBAS DE CASOS EXTREMOS ===\n";
  
  // Test 1: Argumentos con signos iguales en valores
  std::vector<std::string> edge1 = {
    "command",
    "--key=value=with=equals",
    "normal"
  };
  TestTokenization(edge1, "Edge 1 - Valores con múltiples =");
  
  // Test 2: Opciones que parecen posicionales
  std::vector<std::string> edge2 = {
    "test",
    "-",
    "--",
    "---triple",
    "----cuadruple"
  };
  TestTokenization(edge2, "Edge 2 - Guiones múltiples");
  
  // Test 3: Strings vacíos en medio
  std::vector<std::string> edge3 = {
    "cmd",
    "",
    "-o",
    "",
    "arg"
  };
  TestTokenization(edge3, "Edge 3 - Strings vacíos intermedios");
  
  // Test 4: Solo separador
  std::vector<std::string> edge4 = {
    "--"
  };
  TestTokenization(edge4, "Edge 4 - Solo separador");
  
  // Test 5: Opciones al final
  std::vector<std::string> edge5 = {
    "command",
    "posicional1",
    "posicional2",
    "-o"
  };
  TestTokenization(edge5, "Edge 5 - Opción después de posicionales");
}

int main() {
  std::cout << "INICIANDO PRUEBAS DEL SISTEMA DE TOKENIZACIÓN\n";
  std::cout << "=============================================\n";
  
  try {
    // Ejecutar pruebas de aserción (validaciones estrictas)
    RunAssertionTests();
    
    // Ejecutar pruebas comprehensivas
    RunComprehensiveTests();
    
    // Ejecutar casos extremos
    RunEdgeCaseTests();
    
    std::cout << "\n=============================================\n";
    std::cout << "TODAS LAS PRUEBAS COMPLETADAS EXITOSAMENTE\n";
    
  } catch(const std::exception& e) {
    std::cerr << "\n❌ ERROR en pruebas: " << e.what() << std::endl;
    return 1;
  } catch(...) {
    std::cerr << "\n❌ ERROR desconocido en pruebas" << std::endl;
    return 1;
  }
  
  return 0;
}
