cmake_minimum_required(VERSION 3.20)

project(
  c-files
  VERSION 1.0
  LANGUAGES CXX
)

# =========================
# Configuración global
# =========================
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
    # -------------------------
    # Commands
    # -------------------------
    src/commands/list/list.cpp
    src/commands/list/list.h

    # -------------------------
    # Core pipeline
    # -------------------------
    src/core/tokenization/tokenization.cpp
    src/core/tokenization/tokenization.h

    src/core/validation/validation.cpp
    src/core/validation/validation.h

    src/core/classification/classification.cpp
    src/core/classification/classification.h

    src/core/execution/execution.cpp
    src/core/execution/execution.h

    # -------------------------
    # System - registry
    # -------------------------
    src/system/registry/command/command_registry.cpp
    src/system/registry/command/command_registry.h
    src/system/registry/command/register_all.cpp
    src/system/registry/command/register_all.h

    src/system/registry/error/error_registry.cpp
    src/system/registry/error/error_registry.h

    src/system/registry/option/option_registry.cpp
    src/system/registry/option/option_registry.h
    src/system/registry/option/register_all.cpp
    src/system/registry/option/register_all.h

    # -------------------------
    # System - errors
    # -------------------------
    src/system/errors/data_error_register.cpp
    src/system/errors/data_error_register.h
    src/system/errors/print_error.cpp
    src/system/errors/print_error.h

    # -------------------------
    # Utils
    # -------------------------
    src/utils/date_validator.cpp
    src/utils/date_validator.h
    src/utils/string_utils.cpp
    src/utils/string_utils.h
)

# -------------------------
# Public API headers
# -------------------------
target_sources(cfiles_core
  PUBLIC
    src/system/types/CommandMetaData.h
    src/system/types/DataError.h
    src/system/types/OptionMetaData.h
    src/system/types/Token.h
    src/system/types/TokenGroup.h
    src/system/types/TypeToken.h
    src/system/types/ValidationError.h
    src/system/types/ValuePolicy.h
    src/system/types/ValueType.h
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
  target_compile_options(cfiles_core
    PRIVATE
      -fsanitize=address,undefined
      -fno-omit-frame-pointer
      -g
  )
  target_link_options(c-files
    PRIVATE
      -fsanitize=address,undefined
  )
endif()

