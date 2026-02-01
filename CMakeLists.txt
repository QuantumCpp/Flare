cmake_minimum_required(VERSION 3.20)

project(
  c-files
  VERSION 1.0
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_SANITIZERS "Enable sanitizers" ON)

# =========================
# Librería core
# =========================
add_library(cfiles_core STATIC)

target_sources(cfiles_core
  PRIVATE
    src/Commands/CommandList/list.cpp

    src/PipelineProcees/ProccesOfClasification/ProceesOfClasification.cpp
    src/PipelineProcees/ProccesOfTokenization/ProceesOfTokenization.cpp
    src/PipelineProcees/ProccessOfExcute/Execute.cpp
    src/PipelineProcees/ProceesOfValidationTokens/ProceesOfValidationTokens.cpp

    src/SystemUtilites/CommandRegister/CommandRegister.cpp
    src/SystemUtilites/MessageErrorDetail/MessageError.cpp
    src/SystemUtilites/MessageErrorDetail/PrintErroDetail/PrintErrorDetail.cpp
    src/SystemUtilites/MessageErrorDetail/RegisterError/RegisterError.cpp
    src/SystemUtilites/OptionRegistry/OptionRegistry.cpp

    src/Utils/IsValidatedDate/IsValidatedDate.cpp
    src/Utils/RegisterAllCommands/RegisterAllCommands.cpp
    src/Utils/RegisterAllError/RegisterAllError.cpp
    src/Utils/RegisterAllOptions/RegisterAllOptions.cpp
    src/Utils/StartWith/StartWith.cpp
)

target_include_directories(cfiles_core
  PUBLIC
    src
)

target_compile_options(cfiles_core
  PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

# =========================
# Ejecutable
# =========================
add_executable(c-files
  src/main.cpp
)

target_link_libraries(c-files
  PRIVATE
    cfiles_core
)

# =========================
# Sanitizers
# =========================
if(ENABLE_SANITIZERS AND CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_options(cfiles_core PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer -g)
  target_link_options(c-files PRIVATE -fsanitize=address,undefined)
endif()
