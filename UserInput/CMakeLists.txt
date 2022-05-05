cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(BootCampProject
  VERSION 1.0
  LANGUAGES CXX
)

add_executable(ui
  src/main.cpp
  src/ui.cpp
  ../Common/src/socketcan.cpp
)

add_subdirectory(test)

target_link_libraries(ui
PUBLIC
  ncurses
  pthread
)

target_include_directories(ui
PUBLIC
  ../Common/include
  include
)
