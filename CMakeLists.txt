cmake_minimum_required (VERSION 3.2)
project (SimpleCompiler)

# The version number.
set (SimpleCompiler_VERSION_MAJOR 1)
set (SimpleCompiler_VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${CMAKE_SOURCE_DIR}/SimpleCompilerConfig.h.in"
  "${CMAKE_SOURCE_DIR}/include/SimpleCompilerConfig.h"
)

add_compile_options(-std=c++11)

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
set (youroutputdirectory ${CMAKE_BINARY_DIR})

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${youroutputdirectory} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${youroutputdirectory} )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${youroutputdirectory} )
# Second, for multi-config builds (e.g. msvc)
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${youroutputdirectory} )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${youroutputdirectory} )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${youroutputdirectory} )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

include(cotire)
include(DownloadProject)

download_project(PROJ                googletest
                 GIT_REPOSITORY      https://github.com/google/googletest.git
                 GIT_TAG             master
)

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})


file(GLOB SOURCES "src/*.*pp")
file(GLOB ENUM_SOURCES "src/Enums/*.hpp")
file(GLOB TEST_SOURCES "tests/*.*pp")
file(GLOB TEST_MOCK_SOURCES "tests/Mocks/*.*pp")
file(GLOB TEST_FIXTURE_FILES "tests/Fixtures/*.c")

# Set properties for this group of files
set_source_files_properties(
  ${TEST_FIXTURE_FILES}
  PROPERTIES
  HEADER_FILE_ONLY TRUE # Since it's just a text file, it doesn't need compiled
  # MACOSX_PACKAGE_LOCATION Resource # <- only do this if you need to copy the file!
)

source_group(
  "" FILES ${SOURCES}
)

source_group(
  "Enums" FILES ${ENUM_SOURCES}
)

source_group(
  "Tests" FILES ${TEST_SOURCES}
)
source_group(
  "Tests\\Mocks" FILES ${TEST_MOCK_SOURCES}
)
source_group(
  "Tests\\Fixtures" FILES ${TEST_FIXTURE_FILES}
)

# Append your resources to the source files you declared.
list(APPEND
  SOURCES
  ${ENUM_SOURCES}
  ${TEST_SOURCES}
  ${TEST_MOCK_SOURCES}
  ${TEST_FIXTURE_FILES}
)

# add the binary tree to the search path for include files
# so that we will find SimpleCompilerConfig.h
include_directories("${PROJECT_SOURCE_DIR}/src" "${PROJECT_SOURCE_DIR}/src/Enums" "${PROJECT_SOURCE_DIR}/tests/Mocks" "${PROJECT_SOURCE_DIR}/include" ${PROJECT_BINARY_DIR})

# add the executable
add_executable (SimpleCompiler ${SOURCES})
target_link_libraries (SimpleCompiler gtest gmock_main)

set_target_properties(SimpleCompiler PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "PrefixHeader.pch")
cotire(SimpleCompiler)


add_custom_command(TARGET SimpleCompiler POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_SOURCE_DIR}/tests/Fixtures/*.c" ${CMAKE_BINARY_DIR}
)

# install(TARGETS SimpleCompiler DESTINATION bin)

# include(CTest)

#define a macro to simplify adding tests, then use it
# macro (do_test arg result)
#   add_test (TutorialComp${arg} Tutorial ${arg})
#   set_tests_properties (TutorialComp${arg}
#     PROPERTIES PASS_REGULAR_EXPRESSION ${result})
# endmacro (do_test)
 
# do a bunch of result based tests
# do_test (25 "25 is 5")
# do_test (-25 "-25 is 0")