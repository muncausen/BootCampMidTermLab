# add_subdirectory(src/mocks)
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ui VERSION 1.0)
set(TEST_NAME ${PROJECT_NAME}_test)
set(CMAKE_THREAD_PREFER_PTHREAD ON)
find_package(Threads REQUIRED)

add_library(ui_test_lib STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/ui.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Common/src/socketcan.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/../UserInput/src/engine.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/../UserInput/server.cpp
)
## Include directories
target_include_directories(
    ui_test_lib
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../UserInput
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Common/include
    
)

add_executable(${TEST_NAME}
 ${CMAKE_CURRENT_SOURCE_DIR}/unit/ui_gtest.cpp) 

## Link libraries
target_link_libraries(${TEST_NAME}
PUBLIC
    ui_test_lib
    curses
    gtest
    gtest_main
    ${GTEST_LIBRARIES} pthread)

## Add test suite to available tests
add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
