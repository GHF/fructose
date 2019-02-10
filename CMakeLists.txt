cmake_minimum_required(VERSION 3.13)

project(MyProject CXX)
enable_testing()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -pedantic)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# TODO(xw): Maybe create add_library/add_executable macro overrides
if(NOT COMMAND add_sanitizers)
  list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/third_party/sanitizers-cmake/cmake")
  find_package(Sanitizers)
endif()

# Define an umbrella target for all subdirectories to add library sources to
add_library(MyLibrary OBJECT)
add_library(MyProject::MyLibrary ALIAS MyLibrary)
target_include_directories(MyLibrary
  PUBLIC
    ${PROJECT_SOURCE_DIR}
)
add_sanitizers(MyLibrary)

# Define an umbrella target for all subdirectories to add test sources to
add_executable(MyTest)
add_test(NAME MyTest COMMAND MyTest)
target_link_libraries(MyTest
  PRIVATE
    MyProject::MyLibrary
    Catch2::Catch2
)
add_sanitizers(MyTest)
add_subdirectory(third_party/Catch2)
add_subdirectory(testing)

# List all subdirectories containing sources
add_subdirectory(hello)
