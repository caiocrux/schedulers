# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(schedulers VERSION 1.0.0 LANGUAGES CXX)

# Global CMake variables are set here
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Project/Library Names
set(EXECUTABLE_NAME "scheduler")


include(FetchContent)

FetchContent_Declare(
  matplotlib-cpp
  GIT_REPOSITORY https://github.com/lava/matplotlib-cpp.git
  GIT_TAG        master
)
FetchContent_MakeAvailable(matplotlib-cpp)

FetchContent_Declare(
  cxxopts
  GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
  GIT_TAG v3.2.1
)
FetchContent_MakeAvailable(cxxopts)

add_subdirectory(lib)
add_subdirectory(app)
