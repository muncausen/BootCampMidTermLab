cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(BootCampProject
  VERSION 1.0
  LANGUAGES CXX
)

# Use -DBUILD_TESTS=ON to build tests...
add_definitions(
  -DBUILD_TESTS
  -DGENERATE_DOCS
)

add_subdirectory(UserInput)
add_subdirectory(Emulator)

if(BUILD_TESTS)
  add_definitions(ui private=public)
endif(BUILD_TESTS)

target_compile_options(ui
PUBLIC
  -Wall
  -Wextra
  -Werror
  -Wpedantic
)

if(DEFINED GENERATE_DOCS)
  # check if Doxygen is installed
  find_package(Doxygen)
  if(DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doc/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    # note the option ALL which allows to build the docs together with the application
    add_custom_target(dox ALL
      COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Generating API documentation with Doxygen"
      VERBATIM
    )
  else(DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
  endif(DOXYGEN_FOUND)
endif(DEFINED GENERATE_DOCS)
