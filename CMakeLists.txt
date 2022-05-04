cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(BootCampProject
  VERSION 1.0
  LANGUAGES CXX
)

add_subdirectory(UserInput)
add_subdirectory(Emulator)

target_compile_options(ui
PUBLIC
  -Wall
  -Werror
  -Wpedantic
)
