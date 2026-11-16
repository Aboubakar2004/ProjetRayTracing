cmake_minimum_required(VERSION 3.20)
project(RayTracer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
  add_compile_options(/W4 /permissive-)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Core library: all the logic lives here so it can be unit-tested.
add_library(raytracer_core src/lib/greeting.cpp)
target_include_directories(raytracer_core PUBLIC src/lib)

# Executables
add_executable(hello app/main.cpp)
target_link_libraries(hello PRIVATE raytracer_core)

# Tests
include(CTest)
if(BUILD_TESTING)
  add_subdirectory(tests)
endif()
