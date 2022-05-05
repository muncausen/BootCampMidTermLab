

add_library(drivelib STATIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/can_tranceiver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Common/src/socketcan.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/server.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine.cpp  
)

target_include_directories(
    drivelib
PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Common/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../UserInput/include
    )

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
message(STATUS "---------------------***********IntegrationTest CMakeList************--------------------------")

message(STATUS "All include directories")

get_property(dirs TARGET ${PROJECT_NAME} PROPERTY INCLUDE_DIRECTORIES)

foreach(dir ${dirs})

  message(STATUS "dir='${dir}'")

endforeach()

message(STATUS "-----------------------------------------------------------------------")
# macro(print_all_variables)

#     message(STATUS "print_all_variables------------------------------------------{")

#     get_cmake_property(_variableNames VARIABLES)

#     foreach (_variableName ${_variableNames})

#         message(STATUS "${_variableName}=${${_variableName}}")

#     endforeach()

#     message(STATUS "print_all_variables------------------------------------------}")

# endmacro()



# print_all_variables()

# End debugger help

# =============================================================================