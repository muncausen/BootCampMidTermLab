

add_library(drivelib STATIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/can_receiver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/socketcan.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/server.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/src/gear.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/src/socketcan.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/src/wheel.cpp
#    
)

target_include_directories(
    drivelib
PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include)



add_executable(DriveLine
 ${CMAKE_CURRENT_SOURCE_DIR}/../main.cpp) 
 
#add_executable(runTests test_mini.cpp)
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


target_link_libraries(DriveLine PUBLIC 
drivelib
gtest
gtest_main
${GTEST_LIBRARIES} pthread)
#add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
