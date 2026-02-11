cmake_minimum_required(VERSION 3.20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
  Flare
  VERSION 1.0
  LANGUAGES CXX
)

# =========================
# Configuración global
# =========================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_SANITIZERS "Enable sanitizers" ON)

# =========================
# Búsqueda recursiva de archivos
# =========================
file(GLOB_RECURSE FLARE_SOURCES
  "src/commands/*.cpp"
  "src/core/tokenization/*.cpp"
  "src/core/validation/*.cpp"
  "src/core/classification/*.cpp"
  "src/core/execution/*.cpp"
  "src/system/registry/command/*.cpp"
  "src/system/registry/error/*.cpp"
  "src/system/registry/option/*.cpp"
  "src/system/errors/*.cpp"
  "src/utils/*.cpp"
)

file(GLOB_RECURSE FLARE_HEADERS
  "src/commands/*.h"
  "src/core/tokenization/*.h"
  "src/core/validation/*.h"
  "src/core/classification/*.h"
  "src/core/execution/*.h"
  "src/system/registry/command/*.h"
  "src/system/registry/error/*.h"
  "src/system/registry/option/*.h"
  "src/system/errors/*.h"
  "src/system/types/*.h"
  "src/utils/*.h"
)

# Excluir main.cpp de las fuentes de la librería
list(FILTER FLARE_SOURCES EXCLUDE REGEX ".*main\\.cpp$")

# =========================
# Librería core
# =========================
add_library(flare_core STATIC
  ${FLARE_SOURCES}
  ${FLARE_HEADERS}
)

target_include_directories(flare_core
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(flare_core
  PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

# =========================
# Ejecutable
# =========================
add_executable(flare
  src/main.cpp
)

target_link_libraries(flare
  PRIVATE
    flare_core
)

# =========================
# Sanitizers
# =========================
if(ENABLE_SANITIZERS AND CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_options(flare_core
    PRIVATE
      -fsanitize=address,undefined
      -fno-omit-frame-pointer
      -fno-optimize-sibling-calls
      -g
      -O0
  )
  target_link_options(flare
    PRIVATE
      -fsanitize=address,undefined
      -rdynamic
  )
endif()

# =========================
# Instalación
# =========================
install(TARGETS flare
  RUNTIME DESTINATION bin
)

# =========================
# Información de compilación
# =========================
message(STATUS "Flare ${PROJECT_VERSION}")
message(STATUS "Found ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
list(LENGTH FLARE_SOURCES SOURCE_COUNT)
message(STATUS "Compiling ${SOURCE_COUNT} source files")
