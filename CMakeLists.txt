cmake_minimum_required(VERSION 3.20)
project(
  database_in_memory
  VERSION 1.0
  LANGUAGES CXX
)

add_executable(
  database_in_memory
  src/main.cpp
)

target_compile_features(database_in_memory PRIVATE cxx_std_23)
target_compile_options(database_in_memory PRIVATE -Wall -Wextra -Wpedantic)
option(ENABLE_SANITIZERS "Enable sanitizers" ON)

if(ENABLE_SANITIZERS AND CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_options(database_in_memory PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer -g)
  target_link_options(database_in_memory PRIVATE -fsanitize=address,undefined)

endif()

