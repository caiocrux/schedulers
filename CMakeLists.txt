# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(schedulers LANGUAGES CXX)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

FetchContent_Declare(
  matplotlib-cpp
  GIT_REPOSITORY https://github.com/lava/matplotlib-cpp.git
  GIT_TAG        master
)

FetchContent_MakeAvailable(matplotlib-cpp)

add_executable(schedulers schedulers.cc)

target_include_directories(schedulers PRIVATE ${matplotlib-cpp_SOURCE_DIR})

find_package(Python3 COMPONENTS Development NumPy REQUIRED)
target_link_libraries(schedulers Python3::Python Python3::NumPy)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(schedulers PRIVATE -Wall -Wextra -Wpedantic -g)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(schedulers PRIVATE /W4)
endif()

