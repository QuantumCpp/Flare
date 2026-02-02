#!/bin/bash

# Script de reestructuración del File Manager
# Ejecutar desde la raíz del proyecto

echo "🔄 Iniciando reestructuración del proyecto..."

# ============================================
# PASO 1: Crear nueva estructura de directorios
# ============================================

echo "📁 Creando nueva estructura de directorios..."

mkdir -p src/commands/list
mkdir -p src/core/tokenization
mkdir -p src/core/classification
mkdir -p src/core/validation
mkdir -p src/core/execution
mkdir -p src/system/registry/command
mkdir -p src/system/registry/option
mkdir -p src/system/registry/error
mkdir -p src/system/types
mkdir -p src/system/errors
mkdir -p src/utils
mkdir -p tests
mkdir -p docs

# ============================================
# PASO 2: Mover comandos
# ============================================

echo "📦 Moviendo comandos..."

mv src/Commands/CommandList/list.cpp src/commands/list/
mv src/Commands/CommandList/list.h src/commands/list/

# ============================================
# PASO 3: Mover pipeline (core)
# ============================================

echo "⚙️  Moviendo pipeline core..."

# Tokenization
mv src/PipelineProcees/ProccesOfTokenization/ProceesOfTokenization.cpp src/core/tokenization/tokenization.cpp
mv src/PipelineProcees/ProccesOfTokenization/ProccesOfTokenization.h src/core/tokenization/tokenization.h

# Classification
mv src/PipelineProcees/ProccesOfClasification/ProceesOfClasification.cpp src/core/classification/classification.cpp
mv src/PipelineProcees/ProccesOfClasification/ProceesOfClasification.h src/core/classification/classification.h

# Validation
mv src/PipelineProcees/ProceesOfValidationTokens/ProceesOfValidationTokens.cpp src/core/validation/validation.cpp
mv src/PipelineProcees/ProceesOfValidationTokens/ProceesOfValidationTokens.h src/core/validation/validation.h

# Execution
mv src/PipelineProcees/ProccessOfExcute/Execute.cpp src/core/execution/execution.cpp
mv src/PipelineProcees/ProccessOfExcute/Execute.h src/core/execution/execution.h

# ============================================
# PASO 4: Mover sistema de registros
# ============================================

echo "🗄️  Moviendo registros..."

# Command Registry
mv src/SystemUtilites/CommandRegister/CommandRegister.cpp src/system/registry/command/command_registry.cpp
mv src/SystemUtilites/CommandRegister/CommandRegister.h src/system/registry/command/command_registry.h

# Option Registry
mv src/SystemUtilites/OptionRegistry/OptionRegistry.cpp src/system/registry/option/option_registry.cpp
mv src/SystemUtilites/OptionRegistry/OptionRegistry.h src/system/registry/option/option_registry.h

# Error Registry
mv src/SystemUtilites/MessageErrorDetail/RegisterError/RegisterError.cpp src/system/registry/error/error_registry.cpp
mv src/SystemUtilites/MessageErrorDetail/RegisterError/RegisterError.h src/system/registry/error/error_registry.h

# ============================================
# PASO 5: Mover tipos (enums y structs)
# ============================================

echo "📋 Moviendo tipos..."

# Enums
mv src/SystemUtilites/EnumsClass/TypeToken.h src/system/types/
mv src/SystemUtilites/EnumsClass/ValidationError.h src/system/types/
mv src/SystemUtilites/EnumsClass/ValuePolicy.h src/system/types/
mv src/SystemUtilites/EnumsClass/ValueType.h src/system/types/

# Structs
mv src/SystemUtilites/Structs/Token.h src/system/types/
mv src/SystemUtilites/Structs/TokenGroup.h src/system/types/
mv src/SystemUtilites/Structs/CommandMetaData.h src/system/types/
mv src/SystemUtilites/Structs/OptionMetaData.h src/system/types/
mv src/SystemUtilites/Structs/DataError.h src/system/types/

# ============================================
# PASO 6: Mover sistema de errores
# ============================================

echo "❌ Moviendo sistema de errores..."

# Print error detail (fix typo ErroDetail → ErrorDetail)
mv src/SystemUtilites/MessageErrorDetail/PrintErroDetail/PrintErrorDetail.cpp src/system/errors/print_error.cpp
mv src/SystemUtilites/MessageErrorDetail/PrintErroDetail/PrintErrorDetail.h src/system/errors/print_error.h

# Message error
mv src/SystemUtilites/MessageErrorDetail/MessageError.cpp src/system/errors/error_messages.cpp
mv src/SystemUtilites/MessageErrorDetail/MessageError.h src/system/errors/error_messages.h

# ============================================
# PASO 7: Mover utilidades de registro
# ============================================

echo "🔧 Moviendo utilidades..."

# RegisterAllCommands
mv src/Utils/RegisterAllCommands/RegisterAllCommands.cpp src/system/registry/command/register_all.cpp
mv src/Utils/RegisterAllCommands/RegisterAllCommands.h src/system/registry/command/register_all.h

# RegisterAllOptions
mv src/Utils/RegisterAllOptions/RegisterAllOptions.cpp src/system/registry/option/register_all.cpp
mv src/Utils/RegisterAllOptions/RegisterAllOptions.h src/system/registry/option/register_all.h

# RegisterAllError
mv src/Utils/RegisterAllError/RegisterAllError.cpp src/system/registry/error/register_all.cpp
mv src/Utils/RegisterAllError/RegisterAllError.h src/system/registry/error/register_all.h

# ============================================
# PASO 8: Mover utilidades generales
# ============================================

echo "🛠️  Moviendo utilidades generales..."

# StartWith
mv src/Utils/StartWith/StartWith.cpp src/utils/string_utils.cpp
mv src/Utils/StartWith/StartWith.h src/utils/string_utils.h

# IsValidatedDate
mv src/Utils/IsValidatedDate/IsValidatedDate.cpp src/utils/date_validator.cpp
mv src/Utils/IsValidatedDate/IsValidatedDate.h src/utils/date_validator.h

# GeneralLibraries (si existe)
if [ -f src/SystemUtilites/GeneralLibraries/GeneralLibraries.h ]; then
    mv src/SystemUtilites/GeneralLibraries/GeneralLibraries.h src/system/types/common.h
fi

# ============================================
# PASO 9: Mover tests
# ============================================

echo "🧪 Moviendo tests..."

mv src/Test/TokenizationTest.cpp tests/
mv src/Test/ClasificationDataTokenTest.cpp tests/

# ============================================
# PASO 10: Mover documentación
# ============================================

echo "📚 Organizando documentación..."

mv Desing.md docs/DESIGN.md
mv README.md ./README.md  # Mantener en raíz

# ============================================
# PASO 11: Limpiar directorios vacíos
# ============================================

echo "🧹 Limpiando directorios vacíos..."

rm -rf src/Commands
rm -rf src/PipelineProcees
rm -rf src/SystemUtilites
rm -rf src/Utils
rm -rf src/Test

# ============================================
# PASO 12: Crear README en subdirectorios
# ============================================

echo "📝 Creando READMEs descriptivos..."

cat > src/commands/README.md << 'EOF'
# Commands

Command implementations for the CLI.

Each command should be in its own directory with:
- `<command>.cpp` - Implementation
- `<command>.h` - Header
EOF

cat > src/core/README.md << 'EOF'
# Core Pipeline

The main processing pipeline stages:
1. **Tokenization** - Parse raw arguments into tokens
2. **Classification** - Group and normalize tokens
3. **Validation** - Verify semantic correctness
4. **Execution** - Execute the validated command
EOF

cat > src/system/README.md << 'EOF'
# System

Core system components:
- **registry/** - Command, option, and error registries
- **types/** - Enums and struct definitions
- **errors/** - Error handling and messaging
EOF

cat > src/utils/README.md << 'EOF'
# Utilities

Shared utility functions used across the project.
EOF

cat > tests/README.md << 'EOF'
# Tests

Test files for the project.

Run with:
```
g++ -std=c++17 -Wall tests/TokenizationTest.cpp ...
```
EOF

# ============================================
# FIN
# ============================================

echo ""
echo "✅ Reestructuración completada!"
echo ""
echo "📊 Nueva estructura:"
tree src/ -L 3

echo ""
echo "⚠️  IMPORTANTE: Ahora debes actualizar:"
echo "   1. CMakeLists.txt con las nuevas rutas"
echo "   2. #include statements en todos los archivos"
echo ""
echo "💡 Sugerencia: Ejecuta 'git status' para revisar cambios"
