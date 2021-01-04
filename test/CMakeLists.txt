cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(CppStandardV2Tests LANGUAGES CXX)

# ---- Options ----

option(ENABLE_TEST_COVERAGE "Enable test coverage" OFF)
option(TEST_INSTALLED_VERSION "Test the version found by find_package" OFF)

# --- Import tools ----

include(../cmake/tools.cmake)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

CPMAddPackage(
  NAME doctest
  GITHUB_REPOSITORY onqtam/doctest
  GIT_TAG 2.3.7
)

if(TEST_INSTALLED_VERSION)
  find_package(CppStandardV2 REQUIRED)
else()
  CPMAddPackage(NAME CppStandardV2 SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
endif()

CPMAddPackage(
  NAME Format.cmake
  GITHUB_REPOSITORY TheLartians/Format.cmake
  VERSION 1.6
  OPTIONS # enable cmake formatting
          "FORMAT_CHECK_CMAKE ON"
)

# ---- Create binary ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
file(GLOB sourcesUtil CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/util/*.cpp)
file(GLOB sourcesString CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/string/*.cpp)
file(GLOB sourcesAlloc CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/alloc/*.cpp)
file(GLOB sourcesConcurrency CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/concurrency/*.cpp)
file(GLOB sourcesAlgo CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/algo/*.cpp)
add_executable(CppStandardV2Tests ${sources} ${sourcesUtil} ${sourcesString} ${sourcesAlloc} ${sourcesConcurrency} ${sourcesAlgo})

find_package (Threads)
target_link_libraries(CppStandardV2Tests doctest CppStandardV2::CppStandardV2 ${CMAKE_THREAD_LIBS_INIT})

set_target_properties(CppStandardV2Tests PROPERTIES CXX_STANDARD 17)

# enable compiler warnings
if(NOT TEST_INSTALLED_VERSION)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(CppStandardV2 PUBLIC -Wall -pedantic -Wextra -pthread ) # -Werror
    set_target_properties(CppStandardV2Tests PROPERTIES LINK_FLAGS "-pthread")
  elseif(MSVC)
    target_compile_options(CppStandardV2 PUBLIC /W3 ) # /WX
    target_compile_definitions(CppStandardV2Tests PUBLIC DOCTEST_CONFIG_USE_STD_HEADERS)
  endif()
endif()

# ---- Add GreeterTests ----

enable_testing()

# Note: doctest and similar testing frameworks can automatically configure CMake tests For other
# testing frameworks add the tests target instead: ADD_TEST(GreeterTests GreeterTests)

include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
doctest_discover_tests(CppStandardV2Tests)

# ---- code coverage ----

if(ENABLE_TEST_COVERAGE)
  target_compile_options(CppStandardV2 PUBLIC -O0 -g -fprofile-arcs -ftest-coverage)
  target_link_options(CppStandardV2 PUBLIC -fprofile-arcs -ftest-coverage)
endif()
