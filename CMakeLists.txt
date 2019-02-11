cmake_minimum_required(VERSION 3.13)

project(Fructose CXX)
enable_testing()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -pedantic)
add_compile_options(-fwrapv)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# TODO(xw): Maybe create add_library/add_executable macro overrides
if(NOT COMMAND add_sanitizers)
  list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/third_party/sanitizers-cmake/cmake")
  find_package(Sanitizers)
endif()

# Define an umbrella target for all subdirectories to add library sources to
add_library(fructose OBJECT)
add_library(Fructose::fructose ALIAS fructose)
target_include_directories(fructose
  PUBLIC
    ${PROJECT_SOURCE_DIR}
)

# Define an umbrella target for all subdirectories to add test sources to
add_executable(fructose-unittest)
add_test(NAME fructose-unittest COMMAND fructose-unittest)
target_link_libraries(fructose-unittest
  PRIVATE
    Catch2::Catch2
    Fructose::catch2-main
    Fructose::fructose
)
add_sanitizers(fructose-unittest)
add_subdirectory(third_party/Catch2)
add_subdirectory(testing)

# List all subdirectories containing sources
add_subdirectory(base)
