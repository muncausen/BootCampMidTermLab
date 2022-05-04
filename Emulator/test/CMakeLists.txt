cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(DriveLine VERSION 1.0)
set(TEST_NAME ${PROJECT_NAME}_test)
set(CMAKE_THREAD_PREFER_PTHREAD ON)
find_package(Threads REQUIRED)

add_library(emu_test_lib STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../DriveLine/src/can_receiver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../DriveLine/src/socketcan.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../DriveLine/src/engine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../DriveLine/server.cpp
)

## Include directories
target_include_directories(
    emu_test_lib
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../DriveLine/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../DriveLine
)

add_executable(${TEST_NAME}
 ${CMAKE_CURRENT_SOURCE_DIR}/unit/emu_gtest.cpp)

## Link libraries
target_link_libraries(${TEST_NAME}
PUBLIC
    emu_test_lib
    gtest
    gtest_main
    ${GTEST_LIBRARIES} pthread)

## Add test suite to available tests
add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
