cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(BootCampProject
  VERSION 1.0
  LANGUAGES CXX
)

# if(DEFINED BUILD_TESTS)
#   add_subdirectory(test)
# endif(DEFINED BUILD_TESTS)

add_library(drivelib
STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/can_tranceiver.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../Common/src/socketcan.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/engine.cpp
)

target_include_directories(drivelib
PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/../Common/include
)

add_executable(simulator
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

target_link_libraries(simulator PUBLIC
  drivelib
  gtest
  gtest_main
  ${GTEST_LIBRARIES} pthread
)
