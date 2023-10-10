cmake_minimum_required(VERSION 3.5)
project(trab_paa VERSION 0.1 LANGUAGES CXX)

# Set C++17 
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the compiling flags
add_compile_options(
  #-g
  -Wall
  -Werror
  -Wextra
  -Wpedantic
  -ansi
  #-Ofast
  -fsanitize=address,undefined
  -lm
)

add_link_options(-fsanitize=address,undefined)

### Application target
## configura o diretório contendo os .hpp
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

## Cria um executável com nome "graf".
add_executable(paa)

target_sources(
  paa
  PRIVATE
    src/main.cpp
)
